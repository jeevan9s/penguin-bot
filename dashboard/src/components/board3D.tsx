"use client";

import { useEffect, useRef, useState } from "react";
import { ToggleGroup, ToggleGroupItem } from "@/components/ui/toggle-group"import * as THREE from "three";

import { STLLoader } from "three/examples/jsm/loaders/STLLoader.js";

interface Board3DProps {
  pitch: number;
  roll: number;
  yaw: number;
}

export default function Board3D({ pitch, roll, yaw }: Board3DProps) {
  const mountRef = useRef<HTMLDivElement>(null);
  const boardRef = useRef<THREE.Group | null>(null);
  const angles = useRef({ pitch, roll, yaw });

  useEffect(() => {
    angles.current = { pitch, roll, yaw };
  }, [pitch, roll, yaw]);

  useEffect(() => {
    const mount = mountRef.current;
    if (!mount) return;

    let cancelled = false;

    const scene = new THREE.Scene();
    const camera = new THREE.PerspectiveCamera(
      40,
      mount.clientWidth / mount.clientHeight,
      0.1,
      100,
    );
    camera.position.set(2, 2.5, 2);
    camera.lookAt(0, 0, 0);

    const renderer = new THREE.WebGLRenderer({ antialias: true, alpha: true });
    renderer.setSize(mount.clientWidth, mount.clientHeight);
    renderer.setPixelRatio(window.devicePixelRatio);
    mount.appendChild(renderer.domElement);

    // Better lighting
    scene.add(new THREE.AmbientLight(0xffffff, 0.8));
    const dirLight = new THREE.DirectionalLight(0xffffff, 1.0);
    dirLight.position.set(5, 10, 7);
    scene.add(dirLight);

    // This group handles the alignment fix
    const alignmentHelper = new THREE.Group();
    scene.add(alignmentHelper);

    // This group handles the IMU rotations
    const boardIMU = new THREE.Group();
    alignmentHelper.add(boardIMU);
    boardRef.current = boardIMU;

    const loader = new STLLoader();
    loader.load(
      "/models/board.stl",
      (geometry) => {
        if (cancelled) return;

        const material = new THREE.MeshStandardMaterial({
          color: 0xeeeeee,
          roughness: 0.5,
        });
        const mesh = new THREE.Mesh(geometry, material);

        geometry.computeBoundingBox();
        const box = geometry.boundingBox!;
        const center = new THREE.Vector3();
        box.getCenter(center);

        // Center the geometry at helpers origin
        geometry.translate(-center.x, -center.y, -center.z);

        // Scale to fit
        const size = new THREE.Vector3();
        box.getSize(size);
        const maxDim = Math.max(size.x, size.y, size.z);
        const scaleFactor = 1.5 / maxDim;
        mesh.scale.setScalar(scaleFactor);
        mesh.rotation.x = -Math.PI / 2;

        boardIMU.add(mesh);
        console.log("STL loaded and aligned flat.");
      },
      undefined,
      (error) => console.error("Error loading STL model:", error),
    );

    // const grid = new THREE.GridHelper(3, 6, 0x1a1a1a, 0x1c1c1c);
    // scene.add(grid);

    let frameId: number;
    const animate = () => {
      const { pitch: p, roll: r, yaw: y } = angles.current;
      if (boardRef.current) {
        boardRef.current.rotation.x = THREE.MathUtils.degToRad(p); 
        boardRef.current.rotation.y = THREE.MathUtils.degToRad(y);
        boardRef.current.rotation.z = THREE.MathUtils.degToRad(r); 
      }
      renderer.render(scene, camera);
      frameId = requestAnimationFrame(animate);
    };
    animate();

    const handleResize = () => {
      if (!mount) return;
      camera.aspect = mount.clientWidth / mount.clientHeight;
      camera.updateProjectionMatrix();
      renderer.setSize(mount.clientWidth, mount.clientHeight);
    };
    const resizeObserver = new ResizeObserver(handleResize);
    resizeObserver.observe(mount);

    return () => {
      cancelled = true;
      cancelAnimationFrame(frameId);
      resizeObserver.disconnect();
      mount.removeChild(renderer.domElement);
      renderer.dispose();
    };
  }, []);

  return (
    <div className="relative bg-[#141414] border border-[#2a2a2a] rounded flex items-center justify-center overflow-hidden">
      <div ref={mountRef} className="w-full h-full" />
      <div className="absolute bottom-3 left-3 flex gap-4 font-mono text-xs text-[#888]">
        <div>
          pitch:{" "}
          <span className="text-[#fff]">{pitch.toFixed(1)}°</span>
        </div>
        <div>
          roll: <span className="text-[#fff]">{roll.toFixed(1)}°</span>
        </div>
        <div>
          yaw: <span className="text-[#fff]">{yaw.toFixed(1)}°</span>
        </div>
      </div>
    </div>
  );
}
# 🚀 Drone ALPHA - PathFinder  

## 📌 Overview  
**Drone ALPHA - PathFinder** is a **logistics simulation project** designed to **navigate autonomous drones** through Türkiye’s provinces using **Stack and Queue** data structures. The mission is to ensure **maximum province coverage** while **avoiding revisits, respecting fuel constraints**, and **handling priority and weather-restricted locations**.  

This project showcases **efficient route planning** through **stack-based backtracking** and **queue-based exploration management**, implementing **array-based static data structures** for optimal memory usage.

---

## 🚀 Features  
✅ **Autonomous Drone Navigation**  
- Starts from **Ankara** and explores **maximum provinces** under fuel limits.  
- Uses **Queue for route planning** and **Stack for backtracking**.  

✅ **Stack-Based Backtracking**  
- Stores visited provinces in a **Last-In-First-Out (LIFO)** structure.  
- Enables **retracing steps** when a dead-end is reached.  

✅ **Queue-Based Exploration**  
- Manages neighboring provinces in a **First-In-First-Out (FIFO)** order.  
- Uses **circular queue** to efficiently handle new exploration paths.  

✅ **Distance Constraints & Fuel Management**  
- Drone can only travel **250 km per move** before needing to refuel.  
- Checks distance matrix for **valid next moves** using `isWithinRange()`.  

✅ **Handling Priority & Restricted Provinces**  
- **Priority provinces** are **visited first** using `enqueuePriority()`.  
- **Weather-restricted provinces** are **skipped** automatically.  

✅ **Efficient Data Handling**  
- **Loads province distance data** from a CSV file.  
- **Maintains visited provinces list** to prevent revisits.  

✅ **Final Route Summary & Output**  
- Displays the **visited provinces sequence**, **total distance covered**, and **priority status**.  
- **Alerts if priority provinces are missed**.  

---

## 📂 Project Structure  

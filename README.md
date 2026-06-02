[![Documentation](https://img.shields.io/badge/docs-doxygen-blue.svg)](https://alexislaurent1321-gif.github.io/Enmesh/)
![Build](https://github.com/alexislaurent1321-gif/Enmesh/actions/workflows/ci.yml/badge.svg)

# Enmesh

Enmesh is a library used to create, manage, and analyze meshes. It is particularly useful for finite element solvers. 
Its features include: 
- Delaunay triangulation for 2D meshes
- Import of .msh files (version 4.1), the parser was chosen based on qnzhou's [mshio](https://github.com/qnzhou/MshIO.git) library
- VTK export for ParaView visualization
- Mesh quality analysis and edge detection
The supported mesh types are triangular, quadrangular, and tetrahedral meshes

The next step will be to implement more complex methods, such as constrained Delaunay. For more information, see the [Upcoming changes](#upcoming-changes) section.

# Project structure

```bash
+---demos           # demo main files to test different features of the project
+---extern          # extern libraries to parse files (submoules)
+---include 
|   +---geometry    # geometrical elements of a mesh
|   +---io          # input/output : functions to load and export meshes
|   \---mesh        # mesh class and processing functions (smoothing, triangulation, quality analysis)
+---models
+---scripts         # .bat and .sh files to compile and execute demos   
\---src
    +---geometry
    +---io
    \---mesh



```


# Features
## Mesh analyzer (`demo/demo_analyzer.cpp`)
The mesh analysis section allows you to view its attributes and detect/highlight edges.

#### hashing
To ensure optimal search performance within the graph and avoid duplicate edges, we construct a hash table. This method involves using a `std::unordered_set` structure with a custom hash function to identify unique edges with an average time complexity of $O(1)$.

#### Exemple
Here, an exemple for a cube : 
```bash
Vertices : 8
Triangles : 12
Unique edges : 18
```

#### Aspect ratio 

The analyzer computes also the aspects ratio of triangles : 
```bash
min aspect ratio : 1.20711
max aspect ratio : 1.20711
mean aspect ratio : 1.20711
```

The triangles that make up a cube are isosceles-right triangles, which corresponds to an aspect ratio of $\simeq 1.2$.


Let there be a triangle with sides a, b, and c. The formula is

$$\frac{abc}{(b+c-a)(c+a-b)(a+b-c)}$$

This is a basic finite element formula : 
- a ratio of 1 corresponds to a perfect equilateral triangle.
- the higher the ratio, the more distorted the triangle becomes, which can hinder the convergence of the solvers.

#### Boundary detection 
Another function of this project is to detect the edges of the mesh if it is open. To do this, we select the edges along the boundary. An edge is considered to belong to the boundary of the region if it belongs to exactly one triangle. 
To evaluate the valence of the edges (the number of triangles they belong to), we create a `std::unordered_map` that stores integers as values and edges as keys. We iterate through the edges of each triangle and increment the value corresponding to the evaluated edge by 1.

Here is an example of a square made up of quadrangles, the edges are displayed in red.

<img width="1466" height="1132" alt="square_loaded" src="https://github.com/user-attachments/assets/c7b8042e-53df-4c1a-a5a6-5cc9c811d534" style="width:50%;" />





The results show that all edges are detected.

### 3D version : `demo/demo_analyzer3D.cpp` : 
The demo allows you to do the same thing with a tetrahedral or hexahedral mesh. Here we use the example of a $9\times9\times9$ cube with a progressive mesh and a different boundary condition for each face. The  aspect ratio is calculated using this [formula](https://docs.salome-platform.org/latest/gui/SMESH/aspect_ratio_3d.html) for tetrahedra and $\frac{\max(h1, h2, h3)}{\min(h1, h2, h3)})$ for hexahedra which $h1,h2,h3$ are the distances between each center of face to its opposite.

<img width="1466" height="1132" alt="cube2" src="https://github.com/user-attachments/assets/65b35596-eaa7-4865-95f9-9d5ab1fdd464" style="width:50%;" />

Boundary conditions : 

<img width="1466" height="1132" alt="cube2_boundaries" src="https://github.com/user-attachments/assets/0356fe1c-cbf1-4d61-baf9-5a83b89eb61c" style="width:50%;" />

> [!WARNING]  
The boundary rendering conflicts with the volume rendering, causing blue flickering on some faces. These issues will be fixed soon.


The statistics match those of Gmsh :


<img width="232" height="204" alt="gmsh_cube_stats" src="https://github.com/user-attachments/assets/e1e2337e-67b5-41a3-baaf-332032b569e0" style="size:50%;" />

```bash
Vertices : 1000
Elements : 729
Unique Quads : 2430
Boundary elements : 486
min aspect ratio : 1
max aspect ratio : 3.07782
mean aspect ratio : 2.08329
```


## Generate a mesh (`demo/demo_generateGrid.cpp`)
Generates a grid with a tag for each boundary condition

<img width="2197" height="1131" alt="grid_bound" src="https://github.com/user-attachments/assets/bcb40053-94a6-466a-a6b1-df2544924f1d" style="width:50%;"/>



## Delaunay triangulation (`demo/demo_triangulation.cpp`)
The final feature, which will be at the heart of the project, involves triangulating a set of points using the Delaunay method. The algorithm used here is the [Bowyer-Watson](https://www.gorillasun.de/blog/bowyer-watson-algorithm-for-delaunay-triangulation/) algorithm. 
### Test on a regular grid
To validate the triangulation, we count the number of triangles and edges and check the ratio. Since the mesh is a grid, we expect a constant ratio of $\simeq 1.2$. Here are the results for a $4\times 4$ cells ($5 \times 5$ points) grid : 
```
Vertices : 25
Triangles : 32
Unique edges : 56
min aspect ratio : 1.20711
max aspect ratio : 1.20711
mean aspect ratio : 1.20711
```

<img width="1209" height="600" alt="grid_triangulated" src="https://github.com/user-attachments/assets/53eee18e-3077-4b87-9eea-634a993a1e06" style="width:50%;"/>

The results are correct.


## Smoothing (`demo/demo_smoothing.cpp`)
A useful method for improving the regularity of a mesh is to apply smoothing. The function depends here on the number of iterations and a factor $\lambda$. 

$$v_i \longleftarrow v_i + \lambda \left( \frac{1}{N_i}\sum_{j=1}^{N_i} v_j - v_i \right)$$

### Boundaries conditions
Using smoothing can improve the quality of a mesh, particularly that of flat 2D meshes. These meshes are always open, which poses a problem because all the vertices quickly converge toward the center to the point where the mesh may eventually disappear. The idea, therefore, is to avoid applying smoothing to the edge edges. 

Here, we take the example of a random set of points that we triangulate and then apply smoothing (until the result stops changing) to: 

<img width="1209" height="600" alt="smooth_before" src="https://github.com/user-attachments/assets/bb634cbb-85b9-46c1-9f07-0cf98881b850" style="width:50%;"/>

```bash
min aspect ratio : 1.00325
max aspect ratio : 104.116
mean aspect ratio : 4.64866
```

<img width="1209" height="600" alt="smooth_after" src="https://github.com/user-attachments/assets/c4aead62-9d83-4d45-9e70-0a6459ec679d" style="width:50%;"/>

```bash
min aspect ratio : 1.0123
max aspect ratio : 3.65891
mean aspect ratio : 1.50397
```
We observe a better average aspect ratio. However, this result can be further improved by refining certain triangles, which will be the next step in the project.


# Upcoming changes
### in the short term
- improve unit testing
- improve the display of 3D mesh (2 files to avoid conflict between the volume and the boundary)

### in the longer term
- **local mesh adjustments :** remove triangles from the mesh, especially if the model contains a hole or is not convex.
- see Constrained Delaunay triangulation
- see advancing front method ([Advancing Front Grid
Generation](http://ebrary.free.fr/Mesh%20Generation/Handbook_of_Grid_%20Generation,1999/chap17.pdf))
- implement Delaunay for tetrhedral meshes
- **mesh simplification :** edge collapse ([A Comprehensive Guide to Mesh Simplification
using Edge Collapse](https://arxiv.org/pdf/2512.19959)) (maybe)


# Compilation and execution
To clone the project : 
```bash
git clone --recurse-submodules https://github.com/alexislaurent1321-gif/Enmesh.git
```

Compilation on Windows (preferably with **MSVC**) or Linux. Use the **VS Code** interface if possible. On Windows, to run ParaView from the command line, add the ParaView bin folder (e.g., `C:\Program Files\ParaView 6.1.0\bin`) to the `PATH` environment variables.

The demos can be run in the `scripts` folder. Scripts are named as follows : `run_{demo}.sh` for Linux or `run_{demo}.bat` for Windows.

Use the following commands : 
- `./scripts/run_{demo}.bat` on Windows
- `bash scripts/run_{demo}.sh` or `wsl sh scripts/run_{demo}.sh` on Linux



### Dependencies
- [mshio](https://github.com/qnzhou/MshIO.git)
- [ParaView](https://www.paraview.org/)

Block Object
============

The block object stores information about blocks. It is used by the chunk object to keep track of each block. Currently the block object has no built in logic

Methods
-------
Block::Block(glm::vec3 pos,BLOCK_TYPES blocktype);
> Constructor for block Object takes in glm::vec3 for the block position and blocktype specifies the type of block.

BlockMesh Object
================
This object is the mesh object used to render blocks. It is used by the render chunk object to generate the mesh used to render the chunk. There are 6 faces stored and each face is used to generate a mesh used to render the chunks.

Methods
-------
BlockMesh::BlockMesh();
>Constructor for block mesh object no input arguments needed.

std::vector<Model> BlockMesh::getModel()
>used to get the specified face.

Chunk Object
============
The chunk object that stores block information the size is determined by chunkSize

Methods
-------

Chunk::Chunk(std::vector<Block*> blocks,glm::vec3 root_pos)
>New constructor used to generate world. Layout:
```
---------------------------------------------------------
|(X,Y,Z)|(X,Y,Z+1)|(X,Y,Z+2)|...|(X,Y+1,Z)|...|(X+1,Y,Z)|
---------------------------------------------------------
```

void Chunk::setMeshes()
>Used to setup mesh used to draw chunk. Creates render chunks and tells then to setup mesh.

void Chunk::draw()
>Tells chunk to tell render chunk to draw themselves

Chunk::~Chunk()
>Just a deconstructor.

World Object
============
Stores information about the world

Layout of chunks in memory
--------------------------

Chunks stored in this->loadedChunk which is a vector<vector<Chunk*>>
The outer most vector stores layers 
World Layout
```
|----Element 1 -------|     y+
|_____________________|     /\
|                     |     |
|----Element 0 -------|     |
|      /\             |     |
|       |             |     |
|     ChunkSize       |     |
|       |             |     |
|      \/             |     |
|_____________________|     |
```
Top down view
```
z+
/\ 
|--------- Root Pos + Chunk_RENDER_DIST -1
|                 |
|                 |
|                 |
| Root Pos - CHUNK_RENDER_DIST
_________________> x+
```
Inner Vector Memory Layout
cooridinate system: (x,z)

```
-------------------------------------------------------------
| (X,Z)  |  (X,Z+1)  | (X,Z+2) | .... |(X+1,Z) | (X+1,Z+1)  |
-------------------------------------------------------------
```
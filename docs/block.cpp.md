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

Chunk::Chunk(glm::vec3 root_pos)
>constructor depricated used in World::shift* need to change to Chunk::Chunk(std::vector<Block*> blocks,glm::vec3 root_pos)

Chunk::Chunk(std::vector<Block*> blocks,glm::vec3 root_pos)
>New constructor used to generate world. Layout of blocks in memory does not matter.

void Chunk::setMeshes()
>Used to setup mesh used to draw chunk. Creates render chunks and tells then to setup mesh.

void Chunk::draw()
>Tells chunk to tell render chunk to draw themselves

Chunk::~Chunk()
>Just a deconstructor.

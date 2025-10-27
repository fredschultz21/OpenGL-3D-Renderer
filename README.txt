OpenGL 3D Renderer

A modern 3D graphics rendering engine built in C++ using OpenGL, GLAD, and GLFW, developed while following Victor Gordan’s “OpenGL Tutorial for Beginners” series. (https://www.youtube.com/playlist?list=PLPaoO-vpZnumdcb4tZc4x5Q-v7CkrQ5Qp
) The goal of this project was to gain a deep understanding of real-time rendering pipelines, shader programming, and GPU resource management through the implementation of lighting, texturing, and model loading systems.

Some miscellaneous notes:

VBO (vertex buffer) in GPU memory
┌─────────────────────────────────┐
│ Index │ Vertex Data                         │
├────────┼────────────────────────┤
│   0    │ Position(0)  Color(0)  TexUV(0)    │  ← used by EBO
│   1    │ Position(1)  Color(1)  TexUV(1)    │  ← used by EBO
│   2    │ Position(2)  Color(2)  TexUV(2)    │  ← used by EBO
│   3    │ Position(3)  Color(3)  TexUV(3)    │  ← used by EBO
│   4    │ Position(4)  Color(4)  TexUV(4)    │  ← unused (for now)
│   5    │ Position(5)  Color(5)  TexUV(5)    │  ← unused (for now)
└────────┴────────────────────────┘

EBO (element buffer)
┌──────────────────────────┐
│ 0 │ 1 │ 2 │ 2 │ 3 │ 0   │ → defines 2 triangles
└──────────────────────────┘


VAO #1
├── EBO = #7
├── Attribute 0:
│    ├── VBO = #5
│    ├── size = 3
│    ├── type = GL_FLOAT
│    ├── stride = 44
│    ├── offset = 0
│    └── enabled = true
└── (other attributes disabled)


Without VAOs, you'd have to do this every frame:
glBindBuffer(GL_ARRAY_BUFFER, vbo);
glVertexAttribPointer(...);
glVertexAttribPointer(...);
glVertexAttribPointer(...);
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

instead of just:
vao.Bind();

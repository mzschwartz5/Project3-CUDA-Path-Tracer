#pragma once

#include <string>
#include <vector>
#include <cuda_runtime.h>
#include "glm/glm.hpp"

#define BACKGROUND_COLOR (glm::vec3(0.0f))

enum GeomType
{
    SPHERE,
    CUBE,
	MESH
};

struct Ray
{
    glm::vec3 origin;
    glm::vec3 direction;
};

struct Triangle {
    int attributeIndex[3];
};

struct Mesh {
	int vertStartIndex;
    int trianglesStartIndex;
	int numTriangles = 0;
	int baseColorUvIndex;
	int normalUvIndex;
	int emissiveUvIndex;
    glm::vec3 boundingBoxMin;
    glm::vec3 boundingBoxMax;
};

struct Geom
{
    enum GeomType type;
    int materialid;
    glm::vec3 translation;
    glm::vec3 rotation;
    glm::vec3 scale;
    glm::mat4 transform;
    glm::mat4 inverseTransform;
    glm::mat4 invTranspose;
    int meshId;
};

struct Material
{
    glm::vec3 color;
    struct
    {
        float exponent;
        glm::vec3 color;
    } specular;
    float hasReflective;
    float hasRefractive;
    float indexOfRefraction;
    float emittance;
	int baseColorTextureId = -1;
	int normalTextureId = -1;
	int emissiveTextureId = -1;
};

struct Texture {
	int width;
	int height;
	int numComponents;
    int size;
	std::vector<glm::vec4> data; // we can use a vector here, because we know the size of the texture
};

struct Camera
{
    glm::ivec2 resolution;
    glm::vec3 position;
    glm::vec3 lookAt;
    glm::vec3 view;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec2 fov;
    glm::vec2 pixelLength;
	float focalLength;
    float apertureRadius;
};

struct RenderState
{
    Camera camera;
    unsigned int iterations;
    int traceDepth;
    std::vector<glm::vec3> image;
    std::string imageName;
};

struct PathSegment
{
    Ray ray;
    glm::vec3 color;
    int pixelIndex;
    int remainingBounces;
};

// Use with a corresponding PathSegment to do:
// 1) color contribution computation
// 2) BSDF evaluation: generate a new ray
struct ShadeableIntersection
{
  float t;
  glm::vec3 surfaceNormal;
  int materialId;
  glm::vec2 baseColorUvs;
  glm::vec2 normalUvs;
  glm::vec2 emissiveUvs;
};

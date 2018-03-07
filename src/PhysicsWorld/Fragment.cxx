#include <BulletCollision/CollisionShapes/btShapeHull.h>
#include <BulletCollision/CollisionShapes/btConvexHullShape.h>

#include <SFML/Graphics.hpp>

#include "Fragment.hxx"

Fragment::Fragment(Mesh* mesh, sf::Vector2i position) : mesh{mesh}{
  // Create a simplified version of the original mesh for optimization purppose
  btConvexHullShape* originalConvexHullShape = new btConvexHullShape();
  for(unsigned int i = 0; i < mesh->vertices.size() / 3; i ++){
    originalConvexHullShape->addPoint(btVector3(
      mesh->vertices.at(3 * i),
      mesh->vertices.at(3 * i + 1),
      mesh->vertices.at(3 * i + 2)
    ));
  }
  hull = new btShapeHull(originalConvexHullShape);
  btScalar margin = originalConvexHullShape->getMargin();
  hull->buildHull(margin);
  convexHullShape = new btConvexHullShape(
    (btScalar*)hull->getVertexPointer(), hull->numVertices());
  delete originalConvexHullShape;

  // Compute inertia of the shape
  mass = mesh->mass;
  inertia = btVector3(0, 0, 0);
  convexHullShape->calculateLocalInertia(1, inertia);

  // Create the motion state
  motionState = new btDefaultMotionState(
    btTransform(btQuaternion(0, 0, 0, 1),
    btVector3(position.x * 4 - 14, position.y * 4 - 14, 0))
  );

  // And the rigid body
  btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(
    mass,
    motionState,
    convexHullShape,
    inertia
  );
  rigidBody = new btRigidBody(fallRigidBodyCI);
}

std::vector<GLfloat> Fragment::getMoveMatrix(){
  btTransform transform;
  rigidBody->getMotionState()->getWorldTransform(transform);
  btScalar _matrix[16];
  transform.getOpenGLMatrix(_matrix);
  std::vector<GLfloat> matrix(
    _matrix,
    _matrix + sizeof _matrix / sizeof _matrix[0]
  );

  return matrix;
};

Fragment::~Fragment(){
  delete convexHullShape;
  delete hull;
  delete motionState;
  delete rigidBody;
}

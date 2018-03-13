#include <vector>
#include <map>

#include <GL/gl.h>

#include <SFML/Graphics.hpp>

#include <btBulletDynamicsCommon.h>

#include "../mesh/Mesh.hxx"
#include "../mesh/meshes.hxx"
#include "../constants.hxx"

#include "PhysicsWorld.hxx"

PhysicsWorld::PhysicsWorld(std::map<int, std::vector<Mesh*>>* fragmentMeshes)
    : fragmentMeshes{fragmentMeshes}{
  // Create dynamics world
  broadphase = new btDbvtBroadphase();
  collisionConfiguration = new btDefaultCollisionConfiguration();
  dispatcher = new btCollisionDispatcher(collisionConfiguration);
  solver = new btSequentialImpulseConstraintSolver;
  dynamicsWorld = new btDiscreteDynamicsWorld(
    dispatcher,
    broadphase,
    solver,
    collisionConfiguration
  );

  // Set gravity
  dynamicsWorld->setGravity(btVector3(0, 0, -9.81));

  // Create the ground as a box:
  groundShape = new btBoxShape(btVector3(16, 16, 0.2));
  groundMotionState = new btDefaultMotionState(
    btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, -0.2)));
  btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(
    0, groundMotionState, groundShape, btVector3(0, 0, 0));
  groundRigidBody = new btRigidBody(groundRigidBodyCI);
  dynamicsWorld->addRigidBody(groundRigidBody);

  // Create another ground as a 2D plane:
  limitGroundShape = new btStaticPlaneShape(btVector3(0, 0, 1), 0);
  limitGroundMotionState = new btDefaultMotionState(
    btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, -40)));
  btRigidBody::btRigidBodyConstructionInfo limitGroundRigidBodyCI(
    0, limitGroundMotionState, limitGroundShape, btVector3(0, 0, 0));
  limitGroundRigidBody = new btRigidBody(limitGroundRigidBodyCI);
  dynamicsWorld->addRigidBody(limitGroundRigidBody);

  // Start the innerClock
  innerClock = new sf::Clock();
};

void PhysicsWorld::collapsePiece(int piece, sf::Vector2i position){
  // Create a fragment for each fragmentMesh of the piece
  int absPiece = abs(piece);
  for(unsigned int i = 0; i < fragmentMeshes->at(absPiece).size(); i++){
    // Create Fragment instance
    GLfloat rotation = piece > 0 ? -90 : 90;
    Fragment* fragment = new Fragment(
      fragmentMeshes->at(absPiece).at(i), position, rotation);

    // Add it to the fragmentPool
    std::pair<int, Fragment*> pair(piece, fragment);
    fragmentPool.push_back(pair);

    // And add it to the world
    dynamicsWorld->addRigidBody(fragment->rigidBody);
  }
};

void PhysicsWorld::simulate(){
  // Simulate the dynamics world
  dynamicsWorld->stepSimulation(innerClock->getElapsedTime().asSeconds(), 7);
  innerClock->restart();
};

PhysicsWorld::~PhysicsWorld(){
  // Delete rigid bodies
  for(unsigned int i = 0; i < fragmentPool.size(); i++)
    delete fragmentPool.at(i).second;
  fragmentPool.clear();

  // Delete ground
  delete groundShape;
  delete groundMotionState;
  delete groundRigidBody;

  // Delete dynamics world
  delete dynamicsWorld;
  delete solver;
  delete dispatcher;
  delete collisionConfiguration;
  delete broadphase;

  // Delete clock
  delete innerClock;
}
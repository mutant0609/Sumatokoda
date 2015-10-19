/*
* Copyright (c) 2006-2009 Erin Catto http://www.box2d.org
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

/* 
 * Base code for CS 251 Software Systems Lab 
 * Department of Computer Science and Engineering, IIT Bombay
 * 
 */

/*#include "../external/src/Box2D/Testbed/Tests/ConveyorBelt.h"
#include "../external/src/Box2D/Testbed/Framework/Render.h"
#include "../external/src/Box2D/Testbed/Tests/SensorTest.h"
#include "../external/src/Box2D/Testbed/Tests/BodyTypes.h"
#include "..//external/src/Box2D/Testbed/Framework/Test.h"*/

#include "cs251_base.hpp"
#include "render.hpp"

#ifdef __APPLE__
  #include <GLUT/glut.h>
#else
  #include "GL/freeglut.h"
#endif
#include <iostream>
#include <cstring>
using namespace std;

#include "dominos.hpp"

namespace cs251  
{
  /**  The is the constructor 
   * This is the documentation block for the constructor.
   */ 
  dominos_t::dominos_t()
  {
    //Ground
    /*! \var b1 
     * \brief pointer to the body ground 
     */ 
    b2Body* b1;  
    {
      
      b2EdgeShape shape; 
      shape.Set(b2Vec2(-90.0f, 0.0f), b2Vec2(90.0f, 0.0f));
      b2BodyDef bd; 
      b1 = m_world->CreateBody(&bd); 
      b1->CreateFixture(&shape, 0.0f);
      cout<<"wake"<<b1->GetContactList()<<"ssup"<<endl;
  //    m_destructionListener.test = this;
  //m_world->SetDestructionListener(&m_destructionListener);
  
  
    }
    m_world->SetContactListener(this);



   // Platform
 /*   {
      b2BodyDef bd;
      bd.position.Set(-5.0f, 5.0f);
      b2Body* body = m_world->CreateBody(&bd);

      b2PolygonShape shape;
      shape.SetAsBox(10.0f, 0.5f);

      b2FixtureDef fd;
      fd.shape = &shape;
      fd.friction = 0.8f;
     body->CreateFixture(&fd);
    }

// Boxes
    for (int32 i = 0; i < 5; ++i)
    {
      b2BodyDef bd;
      bd.type = b2_dynamicBody;
      bd.position.Set(-10.0f + 2.0f * i, 7.0f);
      b2Body* body = m_world->CreateBody(&bd);

      b2PolygonShape shape;
      shape.SetAsBox(0.5f, 0.5f);
      body->CreateFixture(&shape, 20.0f);
    }*/


  //Start of code for so called conveyor belt

//right motor
  {
      b2PolygonShape shape;
      shape.SetAsBox(2.2f, 0.2f);
  
      b2BodyDef bd;
      bd.position.Set(16.0f, 10.0f);
      bd.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd);
      b2FixtureDef *fd = new b2FixtureDef;
      fd->density = 1.f;
      fd->shape = new b2PolygonShape;
      fd->shape = &shape;
      body->CreateFixture(fd);

      b2PolygonShape shape2;
      shape2.SetAsBox(0.2f, 2.0f);
      b2BodyDef bd2;
      bd2.position.Set(16.0f, 10.0f);
      b2Body* body2 = m_world->CreateBody(&bd2);

      b2RevoluteJointDef jointDef;
      jointDef.enableMotor = true;
      jointDef.motorSpeed = 3;
      jointDef.maxMotorTorque = 2;
      jointDef.bodyA = body;
      jointDef.bodyB = body2;
      jointDef.localAnchorA.Set(0,0);
      jointDef.localAnchorB.Set(0,0);
      jointDef.collideConnected = false;
      m_world->CreateJoint(&jointDef);
  //    cout<<"wake"<<body2->GetContactList()<<"ssup"<<endl;
    }
// left motor
    {
      b2PolygonShape shape;
      shape.SetAsBox(2.2f, 0.2f);
  
      b2BodyDef bd;
      bd.position.Set(5.0f, 10.0f);
      bd.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd);
      b2FixtureDef *fd = new b2FixtureDef;
      fd->density = 1.f;
      fd->shape = new b2PolygonShape;
      fd->shape = &shape;
      body->CreateFixture(fd);

      b2PolygonShape shape2;
      shape2.SetAsBox(0.2f, 2.0f);
      b2BodyDef bd2;
      bd2.position.Set(5.0f, 10.0f);
      b2Body* body2 = m_world->CreateBody(&bd2);

      b2RevoluteJointDef jointDef;
      jointDef.enableMotor = true;
      jointDef.motorSpeed = 3;
      jointDef.maxMotorTorque = 2;
      jointDef.bodyA = body;
      jointDef.bodyB = body2;
      jointDef.localAnchorA.Set(0,0);
      jointDef.localAnchorB.Set(0,0);
      jointDef.collideConnected = false;
      m_world->CreateJoint(&jointDef);
      cout<<"wake"<<body2->GetContactList()<<"ssup"<<endl;
    }

    //Left circle as seen bu u
    {
      b2CircleShape shape;
  
      b2FixtureDef fd;
      fd.shape = &shape;
      fd.isSensor = true;
      fd.density = 20.0f;
      fd.friction = 0.1f;
      shape.m_p.Set(5.0f, 10.0f);
      shape.m_radius = 2.2f;
  
    b2BodyDef bd;
    b2Body* body = m_world->CreateBody(&bd);
    body->CreateFixture(&fd);
    cout<<"wake"<<body->GetContactList()<<"ssup"<<endl;
  }

  //Right circle as seen by u

  {
      b2CircleShape shape;
  
      b2FixtureDef fd;
      fd.shape = &shape;
      fd.isSensor = true;
      fd.density = 20.0f;
      fd.friction = 0.1f;
      shape.m_p.Set(16.0f, 10.0f);
      shape.m_radius = 2.2f;
  
    b2BodyDef bd;
    b2Body* body = m_world->CreateBody(&bd);
    body->CreateFixture(&fd);
    cout<<"wake"<<body->GetContactList()<<"ssup"<<endl;
  }

  //horizontal cardboards
  //upper cardboard
  b2Body* b5; 
  {
      b2PolygonShape shape;
      shape.SetAsBox(6.0f, 0.01f);
  
      b2BodyDef bd;
      bd.position.Set(10.5f, 12.4f);
  //    b2Body* body = m_world->CreateBody(&bd);
       b5 = m_world->CreateBody(&bd);
      b5->CreateFixture(&shape, 0.0f);
  //    if (IsTouching()){
      //contact->SetTangentSpeed(5.0f);
      //  body->ApplyForce( b2Vec2(50,0), body->GetWorldCenter() );
   //     body->SetLinearVelocity();
  //  }
   //   cout<<"wake"<<body->GetContactList()<<"ssup"<<endl;
    }
//lower cardboard
    {
      b2PolygonShape shape;
      shape.SetAsBox(6.0f, 0.01f);
  
      b2BodyDef bd;
      bd.position.Set(10.5f, 7.6f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
      cout<<"wake"<<ground->GetContactList()<<"ssup"<<endl;

    }

//The falling Block

 /*   {
      b2BodyDef bd;
      bd.type = b2_dynamicBody;
      bd.position.Set(10.5f,18.0f);
      b2Body* body = m_world->CreateBody(&bd);

      b2PolygonShape shape;
      shape.SetAsBox(0.5f, 0.5f);
      body->CreateFixture(&shape, 20.0f);
    }*/

    //Left circle as seen bu u
 /*   {
 //     b2CircleShape shape;
      b2PolygonShape polygonShape;
      polygonShape.SetAsBox(0.5f, 0.5f);
   //   myBodyDef.position.Set(10,20);
      b2FixtureDef fd;
  //    fd.shape->SetAsBox(0.5f, 0.5f);;
      fd.shape = &polygonShape;
      fd.isSensor = true;
      fd.density = 20.0f;
      fd.friction = 0.1f;
      
      
  
    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    b2Body* body = m_world->CreateBody(&bd);
    bd.position.Set(20.0f, 60.0f);
    body->CreateFixture(&fd);
  }*/

{
  b2PolygonShape shape;
      shape.SetAsBox(1.2f, 1.2f);
  
      b2BodyDef bd;
      bd.position.Set(11.0f, 18.0f);
      bd.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd);
      b2FixtureDef *fd = new b2FixtureDef;
      fd->density = 1.0f;
   //   fd->isSensor = false;

      fd->shape = new b2PolygonShape;
      fd->shape = &shape;
      m_sensor = body->CreateFixture(fd);
      //void* data = "sin";
      //body->SetUserData(data);
    //  cout<<"outside"<<endl;
   //   b2ContactEdge* edge = body->GetContactList();
   //   cout<<edge;
      cout<<"wake"<<body->GetContactList()<<"ssup"<<endl;
   /* for (b2ContactEdge* edge = body->GetContactList(); edge; edge = edge->next){
      cout<<"for";
      if(edge->contact->IsTouching()){
        cout<<"fi";
        const b2Vec2 v(10.0f,10.0f);
        body->SetLinearVelocity(v);*/
  //  }
//}
}

  }
/*void BeginContact(b2Contact* contact)
  {
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();

    cout<<"sup"; 
  }*/

sim_t *sim = new sim_t("Dominos", dominos_t::create);

}

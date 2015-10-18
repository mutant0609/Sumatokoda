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


#include "cs251_base.hpp"
#include "render.hpp"

#ifdef __APPLE__
  #include <GLUT/glut.h>
#else
  #include "GL/freeglut.h"
#endif

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
    }
         
    
    
    //The upper train of small spheres
   {
      b2Body* spherebody;
  
      b2CircleShape circle;
      circle.m_radius = 0.5;
  
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 5.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
    
      for (int i = 0; i < 6; ++i)
  {
    b2BodyDef ballbd;
    ballbd.type = b2_dynamicBody;
    ballbd.position.Set(-22.0f + i*1.0, 17.0f);
    spherebody = m_world->CreateBody(&ballbd);
    spherebody->CreateFixture(&ballfd);
  }
  }

   //The lower train of small spheres
   {
      b2Body* spherebody;
  
      b2CircleShape circle;
      circle.m_radius = 0.5;
  
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 5.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
    
      for (int i = 0; i < 6; ++i)
  {
    b2BodyDef ballbd;
    ballbd.type = b2_dynamicBody;
    ballbd.position.Set(-22.5f + i*1.0, 16.3f);
    spherebody = m_world->CreateBody(&ballbd);
    spherebody->CreateFixture(&ballfd);
  }
  }
    

    //base for keeping balls
    {
      b2PolygonShape shape;
      shape.SetAsBox(2.5f, 0.1f);
  
      b2BodyDef bd;
      bd.position.Set(-20.5f, 14.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }

// left rod of container for keeping balls
    {
      b2PolygonShape shape;
      shape.SetAsBox(0.1f, 2.0f);
  
      b2BodyDef bd;
      bd.position.Set(-23.0f, 16.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }

    // right rod of container for keeping balls
    {
      b2PolygonShape shape;
      shape.SetAsBox(0.1f, 2.0f);
  
      b2BodyDef bd;
      bd.position.Set(-16.0f, 16.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }

    // 3rd rod above pulley
    {
        b2Body* b2;
        b2PolygonShape shape;
        b2FixtureDef resti;
        resti.restitution=1.0;
        const b2Vec2 center(-18.0,12.0);
        shape.SetAsBox(1.5f, 0.1f,center,-0.5f);
        b2BodyDef bd;
        b2 = m_world->CreateBody(&bd);
        b2->CreateFixture(&shape, 10.0f);

    }

//2rd rod above pulley
  /*  {
        b2Body* b2;
        b2PolygonShape shape;
        b2FixtureDef resti;
        resti.restitution=1.0;
        const b2Vec2 center(-14.0,16.0);
        shape.SetAsBox(3.0f, 0.1f,center,0.5f);
        b2BodyDef bd;
        b2 = m_world->CreateBody(&bd);
        b2->CreateFixture(&shape, 10.0f);

    }


    // 1st rod above pulley
    {
        b2Body* b2;
        b2PolygonShape shape;
        b2FixtureDef resti;
        resti.restitution=1.0;
        const b2Vec2 center(-19.0,13.5);
        shape.SetAsBox(3.0f, 0.1f,center,-0.5f);
        b2BodyDef bd;
        b2 = m_world->CreateBody(&bd);
        b2->CreateFixture(&shape, 10.0f);

    }*/

    //The pulley system
   {
      b2BodyDef *bd = new b2BodyDef;
      bd->type = b2_dynamicBody;
      bd->position.Set(-10,15);
      bd->fixedRotation = true;
      
      //The open box left
      b2FixtureDef *fd1 = new b2FixtureDef;
      fd1->density = 10.0;
      fd1->friction = 0.5;
      fd1->restitution = 0.f;
      fd1->shape = new b2PolygonShape;
      b2PolygonShape bs1;
      bs1.SetAsBox(2,0.1, b2Vec2(-19.0f,-15.0f), 0);
      fd1->shape = &bs1;
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 10.0;
      fd2->friction = 0.5;
      fd2->restitution = 0.f;
      fd2->shape = new b2PolygonShape;
      b2PolygonShape bs2;
      bs2.SetAsBox(0.1,2, b2Vec2(-21.0f,-14.0f), 0);
      fd2->shape = &bs2;
      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->density = 10.0;
      fd3->friction = 0.5;
      fd3->restitution = 0.f;
      fd3->shape = new b2PolygonShape;
      b2PolygonShape bs3;
      bs3.SetAsBox(0.1,2, b2Vec2(-17.0f,-14.0f), 0);
      fd3->shape = &bs3;
       
      b2Body* box1 = m_world->CreateBody(bd);
      box1->CreateFixture(fd1);
      box1->CreateFixture(fd2);
      box1->CreateFixture(fd3);

       //The open box right
      b2FixtureDef *fd4 = new b2FixtureDef;
      fd4->density = 10.0;
      fd4->friction = 0.5;
      fd4->restitution = 0.f;
      fd4->shape = new b2PolygonShape;
      b2PolygonShape bs4;
      bs4.SetAsBox(3.0,0.1, b2Vec2(-3.0f,-6.0f), 0);
      fd4->shape = &bs4;
      b2FixtureDef *fd5 = new b2FixtureDef;
      fd5->density = 10.0;
      fd5->friction = 0.5;
      fd5->restitution = 0.f;
      fd5->shape = new b2PolygonShape;
      b2PolygonShape bs5;
      bs5.SetAsBox(0.1,1, b2Vec2(-6.0f,-5.0f), 0);
      fd5->shape = &bs5;
      b2FixtureDef *fd6 = new b2FixtureDef;
      fd6->density = 10.0;
      fd6->friction = 0.5;
      fd6->restitution = 0.f;
      fd6->shape = new b2PolygonShape;
      b2PolygonShape bs6;
      bs6.SetAsBox(0.1,1, b2Vec2(0.0f,-5.0f), 0);
      fd6->shape = &bs6;
       
      b2Body* box2 = m_world->CreateBody(bd);
      box2->CreateFixture(fd4);
      box2->CreateFixture(fd5);
      box2->CreateFixture(fd6);

      // The pulley joint
      b2PulleyJointDef* myjoint = new b2PulleyJointDef();
      b2Vec2 worldAnchorOnBody1(-10, 15); // Anchor point on body 1 in world axis
      b2Vec2 worldAnchorOnBody2(10, 26); // Anchor point on body 2 in world axis
      b2Vec2 worldAnchorGround1(-28.5, 10); // Anchor point for ground 1 in world axis
      b2Vec2 worldAnchorGround2(-13, 10); // Anchor point for ground 2 in world axis
      float32 ratio = 1.0f; // Define ratio
      myjoint->Initialize(box1, box2, worldAnchorGround1, worldAnchorGround2, box1->GetWorldCenter(), box2->GetWorldCenter(), ratio);
      m_world->CreateJoint(myjoint);
    } 

//The revolving horizontal platform
   {
      b2PolygonShape shape;
      shape.SetAsBox(7.0f, 0.2f);
  
      b2BodyDef bd;
      bd.position.Set(-8.0f, 7.5f);
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
      bd2.position.Set(-8.0f, 7.5f);
      b2Body* body2 = m_world->CreateBody(&bd2);

      b2RevoluteJointDef jointDef;
      jointDef.bodyA = body;
      jointDef.bodyB = body2;
      jointDef.localAnchorA.Set(0,0);
      jointDef.localAnchorB.Set(0,0);
      jointDef.collideConnected = false;
      m_world->CreateJoint(&jointDef);
    }


    //negative gravity balls
    {
      b2CircleShape shape;
     // shape.SetAsBox(0.1f, 1.0f);
      shape.m_radius=0.3f;
  
      b2FixtureDef fd;
      fd.shape = &shape;
      fd.density = 20.0f;
      fd.friction = 0.1f;
    
  {
    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.position.Set(0.5f, 1.0f);
    b2Body* body = m_world->CreateBody(&bd);
    body->SetGravityScale(-0.2);
    body->CreateFixture(&fd);
  }

  {
    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.position.Set(1.0f, 1.0f);
    b2Body* body = m_world->CreateBody(&bd);
    body->SetGravityScale(-0.2);
    body->CreateFixture(&fd);
  }

  {
    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.position.Set(-0.5f, 1.0f);
    b2Body* body = m_world->CreateBody(&bd);
    body->SetGravityScale(-0.2);
    body->CreateFixture(&fd);
  }

  {
    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.position.Set(-1.0f, 1.0f);
    b2Body* body = m_world->CreateBody(&bd);
    body->SetGravityScale(-0.2);
    body->CreateFixture(&fd);
  }

  {
    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.position.Set(0.5f, 1.0f);
    b2Body* body = m_world->CreateBody(&bd);
    body->SetGravityScale(-0.2);
    body->CreateFixture(&fd);
  }

  {
    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.position.Set(1.0f, 1.0f);
    b2Body* body = m_world->CreateBody(&bd);
    body->SetGravityScale(-0.2);
    body->CreateFixture(&fd);
  }

  {
    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.position.Set(-0.5f, 1.0f);
    b2Body* body = m_world->CreateBody(&bd);
    body->SetGravityScale(-0.2);
    body->CreateFixture(&fd);
  }

  {
    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.position.Set(-1.0f, 1.0f);
    b2Body* body = m_world->CreateBody(&bd);
    body->SetGravityScale(-0.2);
    body->CreateFixture(&fd);
  }
    }


    //right box to stop table
    {
      b2PolygonShape shape;
      shape.SetAsBox(2.0f, 0.4f);
  
      b2BodyDef bd;
      bd.position.Set(5.0f, 26.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }

    //left box to stop table
    {
      b2PolygonShape shape;
      shape.SetAsBox(2.0f, 0.4f);
  
      b2BodyDef bd;
      bd.position.Set(-5.0f, 26.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }

    //right box to support table
    {
      b2PolygonShape shape;
      shape.SetAsBox(0.1f, 0.4f);
  
      b2BodyDef bd;
      bd.position.Set(4.5f, 14.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }

    //left box to support table
    {
      b2PolygonShape shape;
      shape.SetAsBox(0.1f, 0.4f);
  
      b2BodyDef bd;
      bd.position.Set(-3.0f, 14.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }


// table
    {
      b2PolygonShape shape;
      shape.SetAsBox(7.01f, 0.2f);
  
      b2FixtureDef fd;
      fd.shape = &shape;
      fd.density = 1.0f;
      fd.friction = 0.1f;
    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.position.Set(0.0f, 14.3f);
    b2Body* body = m_world->CreateBody(&bd);
    body->CreateFixture(&fd);
  } 

/////////////////////clamps//////////////////
  //clamp
    {
      b2PolygonShape shape;
      shape.SetAsBox(0.1f, 0.1f);
  
      b2BodyDef bd;
      bd.position.Set(9.0f, 23.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }
    //clamp
    {
      b2PolygonShape shape;
      shape.SetAsBox(0.1f, 0.1f);
  
      b2BodyDef bd;
      bd.position.Set(12.0f, 23.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }
//clamp
    {
      b2PolygonShape shape;
      shape.SetAsBox(0.1f, 0.1f);
  
      b2BodyDef bd;
      bd.position.Set(-9.0f, 23.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }
      //clamp
    {
      b2PolygonShape shape;
      shape.SetAsBox(0.1f, 0.1f);
  
      b2BodyDef bd;
      bd.position.Set(-12.0f, 23.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }

    //////////////////////////////////

///////////left hinge-rod pair involved n formation of table
    {
    b2Body* b2;
    {
      b2PolygonShape shape;
      shape.SetAsBox(0.4f, 0.4f);
  
      b2BodyDef bd;
      bd.position.Set(9.0f, 22.0f);
   //   b2Body* ground = m_world->CreateBody(&bd);
     // ground->CreateFixture(&shape, 0.0f);
      b2 = m_world->CreateBody(&bd);
      b2->CreateFixture(&shape, 10.0f);
      
    }
    
    b2Body* b4;
    {
      b2PolygonShape shape;
      shape.SetAsBox(3.2f, 0.1f);
  
      b2FixtureDef fd;
      fd.shape = &shape;
      fd.density = 10.0f;
      fd.friction = 0.1f;

      b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.position.Set(9.0f , 22.0f);
   // b2Body* body = m_world->CreateBody(&bd);
    //body->CreateFixture(&fd);
    b4 = m_world->CreateBody(&bd);
      b4->CreateFixture(&shape, 10.0f);
    }
      b2RevoluteJointDef jd;
      b2Vec2 anchor;
      anchor.Set(9.0f, 22.0f);
      jd.Initialize(b2, b4,anchor);

      m_world->CreateJoint(&jd);
    
    
  }

///////////right hinge-rod pair involved n formation of table

   {
    b2Body* b1;
    {
      b2PolygonShape shape;
      shape.SetAsBox(0.4f, 0.4f);
  
      b2BodyDef bd;
      bd.position.Set(-9.0f, 22.0f);
   //   b2Body* ground = m_world->CreateBody(&bd);
     // ground->CreateFixture(&shape, 0.0f);
      b1 = m_world->CreateBody(&bd);
      b1->CreateFixture(&shape, 10.0f);
      
    }
    
    b2Body* b3;
    {
      b2PolygonShape shape;
      shape.SetAsBox(3.65f, 0.1f);
  
      b2FixtureDef fd;
      fd.shape = &shape;
      fd.density = 10.0f;
      fd.friction = 0.1f;

      b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.position.Set(-9.0f , 22.0f);
    b3 = m_world->CreateBody(&bd);
      b3->CreateFixture(&shape, 10.0f);
    }
      b2RevoluteJointDef jd;
      b2Vec2 anchor;
      anchor.Set(-9.0f, 22.0f);
      jd.Initialize(b1, b3,anchor);

      m_world->CreateJoint(&jd);
  }
  ////////////////////////////////// S starts ////////////////////////////////////
//Top horizontal shelf in S
    {
    b2Body* b2;
    {
      b2PolygonShape shape;
      shape.SetAsBox(6.0f, 0.25f);
  
      b2BodyDef bd;
      bd.position.Set(-31.0f, 40.0f);
   //   b2Body* ground = m_world->CreateBody(&bd);
     // ground->CreateFixture(&shape, 0.0f);
      b2 = m_world->CreateBody(&bd);
      b2->CreateFixture(&shape, 10.0f);
      
    }
    
    b2Body* b4;
    {
      b2PolygonShape shape;
      shape.SetAsBox(0.1f, 2.0f);
  
      b2FixtureDef fd;
      fd.shape = &shape;
      fd.density = 20.0f;
      fd.friction = 0.1f;

      b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.position.Set(-36.5f , 42.25f);
   // b2Body* body = m_world->CreateBody(&bd);
    //body->CreateFixture(&fd);
    b4 = m_world->CreateBody(&bd);
      b4->CreateFixture(&shape, 10.0f);
    }
      b2RevoluteJointDef jd;
      b2Vec2 anchor;
      anchor.Set(-36.5f, 40.0f);
      jd.Initialize(b2, b4,anchor);

      m_world->CreateJoint(&jd);
    
    
  }
// second horizontal shelf in S
  {
    b2Body* b5;
    {
      b2PolygonShape shape;
      shape.SetAsBox(6.0f, 0.25f);
  
      b2BodyDef bd;
      bd.position.Set(-31.0f, 35.3f);
   //   b2Body* ground = m_world->CreateBody(&bd);
     // ground->CreateFixture(&shape, 0.0f);
      b5 = m_world->CreateBody(&bd);
      b5->CreateFixture(&shape, 10.0f);
      
    }
    
    b2Body* b7;
    {
      b2PolygonShape shape;
      shape.SetAsBox(0.1f, 2.0f);
  
      b2FixtureDef fd;
      fd.shape = &shape;
      fd.density = 20.0f;
      fd.friction = 0.1f;

      b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.position.Set(-25.5f , 37.25f);
   // b2Body* body = m_world->CreateBody(&bd);
    //body->CreateFixture(&fd);
    b7 = m_world->CreateBody(&bd);
      b7->CreateFixture(&shape, 10.0f);
    }
      b2RevoluteJointDef jd;
      b2Vec2 anchor;
      anchor.Set(-25.5f, 35.3f);
      jd.Initialize(b5, b7,anchor);

      m_world->CreateJoint(&jd);
    
    
  }

  // third horizontal shelf in S
  
    b2Body* b8;
    {
      b2PolygonShape shape;
      shape.SetAsBox(6.0f, 0.25f);
  
      b2BodyDef bd;
      bd.position.Set(-31.0f, 30.6f);
   // b2Body* ground = m_world->CreateBody(&bd);
     // ground->CreateFixture(&shape, 0.0f);
      b8 = m_world->CreateBody(&bd);
      b8->CreateFixture(&shape, 10.0f);
      
    }
    
   
  
    //Dominos on top horizontal shelf on S
   {
      b2PolygonShape shape;
      shape.SetAsBox(0.1f, 1.0f);
  
      b2FixtureDef fd;
      fd.shape = &shape;
      fd.density = 20.0f;
      fd.friction = 0.1f;
    
      for (int i = 0; i < 10; ++i)
  {
    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.position.Set(-35.5f + 1.0f * i, 41.25f);
    b2Body* body = m_world->CreateBody(&bd);
    body->CreateFixture(&fd);
  }
    }

 //Dominos on second horizontal shelf of S
     {
      b2PolygonShape shape;
      shape.SetAsBox(0.1f, 1.0f);
  
      b2FixtureDef fd;
      fd.shape = &shape;
      fd.density = 20.0f;
      fd.friction = 0.1f;
    
      for (int i = 0; i < 8; ++i)
  {
    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.position.Set(-35.5f + 1.0f * i, 38.25f);
    b2Body* body = m_world->CreateBody(&bd);
    body->CreateFixture(&fd);
  }
    }

    //Dominos on third horizontal shelf of S
     {
      b2PolygonShape shape;
      shape.SetAsBox(0.1f, 1.0f);
  
      b2FixtureDef fd;
      fd.shape = &shape;
      fd.density = 20.0f;
      fd.friction = 0.1f;
    
      for (int i = 2; i < 10; ++i)
  {
    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.position.Set(-35.5f + 1.0f * i, 33.25f);
    b2Body* body = m_world->CreateBody(&bd);
    body->CreateFixture(&fd);
  }
    }
    // Box on the S
    {
     b2PolygonShape shape;
      shape.SetAsBox(0.5f, 0.5f);
      b2BodyDef bd3;
      bd3.position.Set(-36.0f, 33.0f);
      bd3.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd3);
      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->density = 0.01f;
      fd3->shape = new b2PolygonShape;
      fd3->shape = &shape;
      body->CreateFixture(fd3);

  }
  //////////////////////////////////S ends ////////////////////////////////////////

  //The pendulum that knocks the dominos off
   {
      b2Body* b3;
      {
  b2PolygonShape shape;
  shape.SetAsBox(0.25f, 0.1f);
    
  b2BodyDef bd;
  bd.position.Set(-25.5f, 40.0f);
  b3 = m_world->CreateBody(&bd);
  b3->CreateFixture(&shape, 10.0f);
      }
  
      b2Body* b6;
      {
  b2PolygonShape shape;
  shape.SetAsBox(0.4f, 0.4f);
    
  b2BodyDef bd;
  bd.type = b2_dynamicBody;
  bd.position.Set(-20.5f, 43.0f);
  b6 = m_world->CreateBody(&bd);
  b6->CreateFixture(&shape, 2.0f);
      }
  
      b2RevoluteJointDef jd;
      b2Vec2 anchor;
      anchor.Set(-25.5f, 50.0f);
      jd.Initialize(b3, b6,anchor);

      m_world->CreateJoint(&jd);
    }
      ///////////////////////// W starts //////////////////////////
    // W 1st seg
     for(int i=0;i<7;i++)
    {
        b2Body* b2;
        b2PolygonShape shape;
        b2FixtureDef resti;
        resti.restitution=1.0;
        const b2Vec2 center((-20.0+1.0*i),(40.0-0.2*i*i));
        shape.SetAsBox(1.5f, 0.1f,center,-1.0f);
        b2BodyDef bd;
        b2 = m_world->CreateBody(&bd);
        b2->CreateFixture(&shape, 10.0f);

    }

    //W 4th seg
     for(int i=0;i<6;i++)
    {
        b2Body* b2;
        b2PolygonShape shape;
        b2FixtureDef resti;
        resti.restitution=1.0;
        const b2Vec2 center((-1.0*i),(38.0-0.2*i*i));
        shape.SetAsBox(1.0f, 0.1f,center,1.0f);
        b2BodyDef bd;
        b2 = m_world->CreateBody(&bd);
        b2->CreateFixture(&shape, 10.0f);

    }
// W 3rd seg
     for(int i=0;i<5;i++)
    {
        b2Body* b2;
        b2PolygonShape shape;
        b2FixtureDef resti;
        resti.restitution=1.0;
        const b2Vec2 center((-9.0-1.2*i),(36.0-0.2*i*i));
        shape.SetAsBox(1.0f, 0.1f,center,0.6f);
        b2BodyDef bd;
        b2 = m_world->CreateBody(&bd);
        b2->CreateFixture(&shape, 10.0f);

    }
// W 2nd seg
     for(int i=0;i<5;i++)
    {
        b2Body* b2;
        b2PolygonShape shape;
        b2FixtureDef resti;
        resti.restitution=1.0;
        const b2Vec2 center((-10.0+1.2*i),(36.0-0.2*i*i));
        shape.SetAsBox(0.5+0.1*i, 0.1,center,-0.6f);
        b2BodyDef bd;
        b2 = m_world->CreateBody(&bd);
        b2->CreateFixture(&shape, 10.0f);

    }
    //W plank 1

    {
        b2Body* b2;
        b2PolygonShape shape;
        b2FixtureDef resti;
        resti.restitution=1.0;
        const b2Vec2 center((-14.0),(35.0));
        shape.SetAsBox(1.5, 0.1,center,0.0f);
        b2BodyDef bd;
        b2 = m_world->CreateBody(&bd);
        b2->CreateFixture(&shape, 10.0f);
    }

    //W plank 2

    {
        b2Body* b2;
        b2PolygonShape shape;
        b2FixtureDef resti;
        resti.restitution=1.0;
        const b2Vec2 center((-6.0),(35.0));
        shape.SetAsBox(1.5, 0.1,center,0.0f);
        b2BodyDef bd;
        b2 = m_world->CreateBody(&bd);
        b2->CreateFixture(&shape, 10.0f);
    }

    //  launching plank of ball
    {
        b2Body* b2;
        b2PolygonShape shape;
        b2FixtureDef resti;
        resti.restitution=1.0;
        const b2Vec2 center((-20.0),(41.0));
        shape.SetAsBox(1.0, 0.1,center,-0.2f);
        b2BodyDef bd;
        b2 = m_world->CreateBody(&bd);
        b2->CreateFixture(&shape, 10.0f);
    }

    // The ball
  {
      b2Body* spherebody;

      b2CircleShape circle;
      circle.m_radius = 0.4;

      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 8.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 1.0f;

    b2BodyDef ballbd;
    ballbd.type = b2_dynamicBody;

    ballbd.position.Set(-20.0f, 45.0f);
    spherebody = m_world->CreateBody(&ballbd);
    spherebody->CreateFixture(&ballfd);

    }

    //Motor
    {
    b2Body* motorpane;
    {
     b2PolygonShape shape;
     b2BodyDef bd;
     shape.SetAsBox(0.2f, 3.5f);
     bd.position.Set(2.0f, 42.5f);
     bd.type = b2_dynamicBody;
     motorpane = m_world->CreateBody(&bd);
     motorpane->CreateFixture(&shape, 0.5f);

    }
    b2Body* pin;
    {
     b2CircleShape cshape;
     b2BodyDef bd;
     cshape.m_radius = 0.4;
     bd.position.Set(2.0f, 42.5f);
     pin = m_world->CreateBody(&bd);
     pin->CreateFixture(&cshape, 0.5f);
    }

  b2RevoluteJointDef revoluteJointDef;
  revoluteJointDef.bodyA = motorpane;
  revoluteJointDef.bodyB = pin;
  revoluteJointDef.collideConnected = false;
  revoluteJointDef.localAnchorA.Set(0,0);
  revoluteJointDef.localAnchorB.Set(0,0);
  revoluteJointDef.enableMotor = true;
  revoluteJointDef.maxMotorTorque = 1000.0f;
  revoluteJointDef.motorSpeed = 9.0f;
  b2RevoluteJoint* m_joint = (b2RevoluteJoint*)m_world->CreateJoint( &revoluteJointDef );
  }

     ////////////////////////// W ends  //////////////////////////

  //////////////////////////////G starts /////////////////////////
 //G part
  {
      b2PolygonShape shape;
      shape.SetAsBox(0.25f, 4.0f);

      b2BodyDef bd;
      bd.position.Set(29.0f, 30.0f);
      b2Body* g1 = m_world->CreateBody(&bd);
      g1->CreateFixture(&shape, 0.0f);

      shape.SetAsBox(4.0f,0.25f);
      bd.position.Set(33.0f, 25.5f);
      b2Body* g2 = m_world->CreateBody(&bd);
       g2->CreateFixture(&shape, 0.0f);

     const b2Vec2 center(33.0f,41.0f);
     shape.SetAsBox(4.0f,0.25f,center,0.0f);
     b2BodyDef bd2;
     b2Body* stop = m_world->CreateBody(&bd2);
     stop->CreateFixture(&shape, 10.0f);


       shape.SetAsBox(0.6f, 3.0f);
        bd.position.Set(38.0f, 29.0f);
      b2Body* g3 = m_world->CreateBody(&bd);
      g3->CreateFixture(&shape, 0.0f);

      shape.SetAsBox(0.6f, 0.6f);
        bd.position.Set(38.0f, 33.0f);
        bd.type = b2_dynamicBody;
      b2Body* g4 = m_world->CreateBody(&bd);
      g4->CreateFixture(&shape, 0.0f);



    }


    //G-Door
  {
  b2Body* top;
  {
     b2CircleShape cshape;
     b2BodyDef bd;
     cshape.m_radius = 0.4;
     bd.position.Set(29.0f, 38.0f);
     top = m_world->CreateBody(&bd);
     top->CreateFixture(&cshape, 0.5f);
  }
  b2Body* door;
  {
    b2PolygonShape shape;
    shape.SetAsBox(0.25f,3.0f);
    b2BodyDef doordef;
    doordef.type=b2_dynamicBody;
    doordef.position.Set(29.0f,38.0f);
    door=m_world->CreateBody(&doordef);
    door->CreateFixture(&shape,0.5f);
  }

  b2RevoluteJointDef revoluteJointDef;
  revoluteJointDef.bodyA = top;
  revoluteJointDef.bodyB = door;
  revoluteJointDef.collideConnected = false;
  revoluteJointDef.localAnchorA.Set(0.0f,0.0f);//the top right corner of the box
  revoluteJointDef.localAnchorB.Set(0.0f,0.0f);//center of the circle

  b2RevoluteJoint* m_joint2 = (b2RevoluteJoint*)m_world->CreateJoint( &revoluteJointDef );
  }

  //////////////////////////////G ends  //////////////////////////

    ////////////////////////// A starts ////////////////////////////
     //start of code for A

    //middle horizontal shelf

    {
      b2PolygonShape shape;
      shape.SetAsBox(6.0f, 0.15f, b2Vec2(-20.f,20.f), 0.0f);
  
      b2BodyDef bd;
      bd.position.Set(35.0f, 15.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }
//firstdown1 from the middle hor shelf
    {
      b2PolygonShape shape;
      shape.SetAsBox(1.0f, 0.15f, b2Vec2(-20.f,20.f), 0.0f);
  
      b2BodyDef bd;
      bd.position.Set(27.0f, 13.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }
//firstdown2 from mid hor shelf
    {
      b2PolygonShape shape;
      shape.SetAsBox(1.0f, 0.15f, b2Vec2(-20.f,20.f), 0.0f);
  
      b2BodyDef bd;
      bd.position.Set(43.0f, 13.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }
//second1 from mid hor shelf
    {
      b2PolygonShape shape;
      shape.SetAsBox(1.0f, 0.15f, b2Vec2(-20.f,20.f), 0.0f);
  
      b2BodyDef bd;
      bd.position.Set(45.0f, 11.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }
//second2 from mid hor shelf
    {
      b2PolygonShape shape;
      shape.SetAsBox(1.0f, 0.15f, b2Vec2(-20.f,20.f), 0.0f);
  
      b2BodyDef bd;
      bd.position.Set(25.0f, 11.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }
//firstup1 from mid hor shelf
    {
      b2PolygonShape shape;
      shape.SetAsBox(0.3f, 0.15f, b2Vec2(-20.f,20.f), 0.0f);
  
      b2BodyDef bd;
      bd.position.Set(32.0f, 17.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }
//firstup2 from mid hor shelf
    {
      b2PolygonShape shape;
      shape.SetAsBox(0.3f, 0.15f, b2Vec2(-20.f,20.f), 0.0f);
  
      b2BodyDef bd;
      bd.position.Set(38.0f, 17.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }
//top hor shelf
    {
      b2PolygonShape shape;
      shape.SetAsBox(0.5f, 0.15f, b2Vec2(-20.f,20.f), 0.0f);
  
      b2BodyDef bd;
      bd.position.Set(35.0f, 19.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }
    
    //Dominos on A

    {
      b2PolygonShape shape;
      shape.SetAsBox(0.1f, 1.7f);
  
      b2FixtureDef fd;
      fd.shape = &shape;
      fd.density = 20.0f;
      fd.friction = 0.1f;
    
    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.position.Set(15.0f, 47.0f);
    b2Body* body = m_world->CreateBody(&bd);
    body->CreateFixture(&fd);
  
    }

    {
      b2PolygonShape shape;
      shape.SetAsBox(0.1f, 1.7f);
  
      b2FixtureDef fd;
      fd.shape = &shape;
      fd.density = 20.0f;
      fd.friction = 0.1f;
    
    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.position.Set(12.0f, 45.0f);
    b2Body* body = m_world->CreateBody(&bd);
    body->CreateFixture(&fd);
  
    }

    {
      b2PolygonShape shape;
      shape.SetAsBox(0.1f, 1.7f);
  
      b2FixtureDef fd;
      fd.shape = &shape;
      fd.density = 20.0f;
      fd.friction = 0.1f;
    
    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.position.Set(18.0f, 45.0f);
    b2Body* body = m_world->CreateBody(&bd);
    body->CreateFixture(&fd);
  
    }

    {
      b2PolygonShape shape;
      shape.SetAsBox(0.1f, 1.7f);
  
      b2FixtureDef fd;
      fd.shape = &shape;
      fd.density = 20.0f;
      fd.friction = 0.1f;
    
    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.position.Set(9.5f, 41.0f);
    b2Body* body = m_world->CreateBody(&bd);
    body->CreateFixture(&fd);

    }

    {
      b2PolygonShape shape;
      shape.SetAsBox(0.1f, 1.7f);
  
      b2FixtureDef fd;
      fd.shape = &shape;
      fd.density = 20.0f;
      fd.friction = 0.1f;
    
    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.position.Set(20.5f, 41.0f);
    b2Body* body = m_world->CreateBody(&bd);
    body->CreateFixture(&fd);
  
    }

    {
      b2PolygonShape shape;
      shape.SetAsBox(0.1f, 1.7f);
  
      b2FixtureDef fd;
      fd.shape = &shape;
      fd.density = 20.0f;
      fd.friction = 0.1f;
    
    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.position.Set(6.5f, 37.0f);
    b2Body* body = m_world->CreateBody(&bd);
    body->CreateFixture(&fd);

    }

    {
      b2PolygonShape shape;
      shape.SetAsBox(0.1f, 1.7f);
  
      b2FixtureDef fd;
      fd.shape = &shape;
      fd.density = 20.0f;
      fd.friction = 0.1f;
    
    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.position.Set(23.5f, 37.0f);
    b2Body* body = m_world->CreateBody(&bd);
    body->CreateFixture(&fd);
  
    }

    {
      b2PolygonShape shape;
      shape.SetAsBox(0.1f, 1.7f);
  
      b2FixtureDef fd;
      fd.shape = &shape;
      fd.density = 20.0f;
      fd.friction = 0.1f;
  
    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.position.Set(4.5f, 33.0f);
    b2Body* body = m_world->CreateBody(&bd);
    body->CreateFixture(&fd);
  
    }

    {
      b2PolygonShape shape;
      shape.SetAsBox(0.1f, 1.7f);
  
      b2FixtureDef fd;
      fd.shape = &shape;
      fd.density = 20.0f;
      fd.friction = 0.1f;
    
    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.position.Set(25.5f, 33.0f);
    b2Body* body = m_world->CreateBody(&bd);
    body->CreateFixture(&fd);
  
    }

    ////////////////////////// A ends  ////////////////////////////

  }

  sim_t *sim = new sim_t("Dominos", dominos_t::create);
}

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
         
    //Top horizontal shelf in S
    {
    b2Body* b2;
    {
      b2PolygonShape shape;
      shape.SetAsBox(6.0f, 0.25f);
	
      b2BodyDef bd;
      bd.position.Set(-31.0f, 30.0f);
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
    bd.position.Set(-36.5f , 32.25f);
   // b2Body* body = m_world->CreateBody(&bd);
    //body->CreateFixture(&fd);
    b4 = m_world->CreateBody(&bd);
      b4->CreateFixture(&shape, 10.0f);
    }
      b2RevoluteJointDef jd;
      b2Vec2 anchor;
      anchor.Set(-36.5f, 30.0f);
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
      bd.position.Set(-31.0f, 25.3f);
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
    bd.position.Set(-25.5f , 27.25f);
   // b2Body* body = m_world->CreateBody(&bd);
    //body->CreateFixture(&fd);
    b7 = m_world->CreateBody(&bd);
      b7->CreateFixture(&shape, 10.0f);
    }
      b2RevoluteJointDef jd;
      b2Vec2 anchor;
      anchor.Set(-25.5f, 25.3f);
      jd.Initialize(b5, b7,anchor);

      m_world->CreateJoint(&jd);
    
    
  }

  // third horizontal shelf in S
  
    b2Body* b8;
    {
      b2PolygonShape shape;
      shape.SetAsBox(6.0f, 0.25f);
	
      b2BodyDef bd;
      bd.position.Set(-31.0f, 20.6f);
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
	  bd.position.Set(-35.5f + 1.0f * i, 31.25f);
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
	  bd.position.Set(-35.5f + 1.0f * i, 28.25f);
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
	  bd.position.Set(-35.5f + 1.0f * i, 23.25f);
	  b2Body* body = m_world->CreateBody(&bd);
	  body->CreateFixture(&fd);
	}
    }
    // Box on the S
    {
     b2PolygonShape shape;
      shape.SetAsBox(0.5f, 0.5f);
      b2BodyDef bd3;
      bd3.position.Set(-36.0f, 23.0f);
      bd3.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd3);
      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->density = 0.01f;
      fd3->shape = new b2PolygonShape;
      fd3->shape = &shape;
      body->CreateFixture(fd3);

  }
// 1st rod above pulley system
{
    b2Body* b10;
    {
      b2PolygonShape shape;
      shape.SetAsBox(0.09f, 0.1f);
	
      b2BodyDef bd;
      bd.position.Set(8.0f, 26.0f);
   //   b2Body* ground = m_world->CreateBody(&bd);
     // ground->CreateFixture(&shape, 0.0f);
      b10 = m_world->CreateBody(&bd);
      b10->CreateFixture(&shape, 10.0f);
      
    }
    
    b2Body* b11;
    {
      b2PolygonShape shape;
      shape.SetAsBox(0.1f, 5.0f);
  
      b2FixtureDef fd;
      fd.shape = &shape;
      fd.density = 20.0f;
      fd.friction = 0.1f;

      b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.position.Set(7.95f , 29.25f);
   // b2Body* body = m_world->CreateBody(&bd);
    //body->CreateFixture(&fd);
    b11 = m_world->CreateBody(&bd);
      b11->CreateFixture(&shape, 10.0f);
    }
      b2RevoluteJointDef jd;
      b2Vec2 anchor;
      anchor.Set(8.0f, 26.0f);
      jd.Initialize(b10, b11,anchor);

      m_world->CreateJoint(&jd);
    
    
  }

  // body to stop 1st rod above pulley system
  b2Body* b12;
    {
      b2PolygonShape shape;
      shape.SetAsBox(0.1f, 0.1f);
	
      b2BodyDef bd;
      bd.position.Set(2.8f, 32.0f);
   //   b2Body* ground = m_world->CreateBody(&bd);
     // ground->CreateFixture(&shape, 0.0f);
      b12 = m_world->CreateBody(&bd);
      b12->CreateFixture(&shape, 10.0f);
      
    }

// 2nd rod above pulley system
{
    b2Body* b13;
    {
      b2PolygonShape shape;
      shape.SetAsBox(0.09f, 0.1f);
	
      b2BodyDef bd;
      bd.position.Set(9.0f, 29.0f);
   //   b2Body* ground = m_world->CreateBody(&bd);
     // ground->CreateFixture(&shape, 0.0f);
      b13 = m_world->CreateBody(&bd);
      b13->CreateFixture(&shape, 10.0f);
      
    }
   
    b2Body* b14;
    {
      b2PolygonShape shape;
      shape.SetAsBox(0.1f, 5.0f);
  
      b2FixtureDef fd;
      fd.shape = &shape;
      fd.density = 20.0f;
      fd.friction = 0.1f;

      b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.position.Set(9.1f , 34.0f);
   // b2Body* body = m_world->CreateBody(&bd);
    //body->CreateFixture(&fd);
    b14 = m_world->CreateBody(&bd);
      b14->CreateFixture(&shape, 10.0f);
    }
      b2RevoluteJointDef jd;
      b2Vec2 anchor;
      anchor.Set(9.0f, 29.0f);
      jd.Initialize(b13, b14,anchor);

      m_world->CreateJoint(&jd);
    
    
  }

  // body to stop 2nd rod above pulley system
  b2Body* b15;
    {
      b2PolygonShape shape;
      shape.SetAsBox(0.1f, 0.1f);
	
      b2BodyDef bd;
      bd.position.Set(15.0f, 36.0f);
   //   b2Body* ground = m_world->CreateBody(&bd);
     // ground->CreateFixture(&shape, 0.0f);
      b15 = m_world->CreateBody(&bd);
      b15->CreateFixture(&shape, 10.0f);
      
    }

// 3rd rod above pulley system
{
    b2Body* b16;
    {
      b2PolygonShape shape;
      shape.SetAsBox(0.09f, 0.1f);
	
      b2BodyDef bd;
      bd.position.Set(8.5f, 34.0f);
   //   b2Body* ground = m_world->CreateBody(&bd);
     // ground->CreateFixture(&shape, 0.0f);
      b16 = m_world->CreateBody(&bd);
      b16->CreateFixture(&shape, 10.0f);
      
    }
   
    b2Body* b17;
    {
      b2PolygonShape shape;
      shape.SetAsBox(0.1f, 4.0f);
  
      b2FixtureDef fd;
      fd.shape = &shape;
      fd.density = 20.0f;
      fd.friction = 0.1f;

      b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.position.Set(8.4f , 37.5f);
   // b2Body* body = m_world->CreateBody(&bd);
    //body->CreateFixture(&fd);
    b17 = m_world->CreateBody(&bd);
      b17->CreateFixture(&shape, 10.0f);
    }
      b2RevoluteJointDef jd;
      b2Vec2 anchor;
      anchor.Set(8.5f, 34.0f);
      jd.Initialize(b16, b17,anchor);

      m_world->CreateJoint(&jd);
    
    
  }

  // body to stop 3rd rod above pulley system
  b2Body* b18;
    {
      b2PolygonShape shape;
      shape.SetAsBox(0.1f, 0.1f);
	
      b2BodyDef bd;
      bd.position.Set(3.0f, 38.0f);
   //   b2Body* ground = m_world->CreateBody(&bd);
     // ground->CreateFixture(&shape, 0.0f);
      b18 = m_world->CreateBody(&bd);
      b18->CreateFixture(&shape, 10.0f);
      
    }

  
    //Another horizontal shelf
  /*  {
      b2PolygonShape shape;
      shape.SetAsBox(7.0f, 0.25f, b2Vec2(-20.f,20.f), 0.0f);
	
      b2BodyDef bd;
      bd.position.Set(1.0f, 6.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }

*/
    //The pendulum that knocks the dominos off
   {
      b2Body* b3;
      {
	b2PolygonShape shape;
	shape.SetAsBox(0.25f, 0.1f);
	  
	b2BodyDef bd;
	bd.position.Set(-25.5f, 30.0f);
	b3 = m_world->CreateBody(&bd);
	b3->CreateFixture(&shape, 10.0f);
      }
	
      b2Body* b6;
      {
	b2PolygonShape shape;
	shape.SetAsBox(0.4f, 0.4f);
	  
	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	bd.position.Set(-20.5f, 33.0f);
	b6 = m_world->CreateBody(&bd);
	b6->CreateFixture(&shape, 2.0f);
      }
	
      b2RevoluteJointDef jd;
      b2Vec2 anchor;
      anchor.Set(-25.5f, 40.0f);
      jd.Initialize(b3, b6,anchor);

      m_world->CreateJoint(&jd);
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
	  
      for (int i = 0; i < 10; ++i)
	{
	  b2BodyDef ballbd;
	  ballbd.type = b2_dynamicBody;
	  ballbd.position.Set(-6.0f + i*1.0, 42.3f);
	  spherebody = m_world->CreateBody(&ballbd);
	  spherebody->CreateFixture(&ballfd);
	}
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
	  
      for (int i = 0; i < 10; ++i)
	{
	  b2BodyDef ballbd;
	  ballbd.type = b2_dynamicBody;
	  ballbd.position.Set(-5.5f + i*1.0, 42.3f);
	  spherebody = m_world->CreateBody(&ballbd);
	  spherebody->CreateFixture(&ballfd);
	}
	}
    

    //base for keeping balls
    {
      b2PolygonShape shape;
      shape.SetAsBox(5.0f, 0.1f);
	
      b2BodyDef bd;
      bd.position.Set(-2.5f, 42.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }

// left rod of container for keeping balls
    {
      b2PolygonShape shape;
      shape.SetAsBox(0.1f, 2.0f);
	
      b2BodyDef bd;
      bd.position.Set(-7.0f, 44.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }

    // right rod of container for keeping balls
    {
      b2PolygonShape shape;
      shape.SetAsBox(0.1f, 2.0f);
	
      b2BodyDef bd;
      bd.position.Set(5.0f, 44.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }

    

    //The pulley system
   {
      b2BodyDef *bd = new b2BodyDef;
      bd->type = b2_dynamicBody;
      bd->position.Set(-10,15);
      bd->fixedRotation = true;
      
      //The open box left
      b2FixtureDef *fd1 = new b2FixtureDef;
      fd1->density = 15.0;
      fd1->friction = 0.5;
      fd1->restitution = 0.f;
      fd1->shape = new b2PolygonShape;
      b2PolygonShape bs1;
      bs1.SetAsBox(2,0.2, b2Vec2(0.f,-1.9f), 0);
      fd1->shape = &bs1;
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 15.0;
      fd2->friction = 0.5;
      fd2->restitution = 0.f;
      fd2->shape = new b2PolygonShape;
      b2PolygonShape bs2;
      bs2.SetAsBox(0.2,2, b2Vec2(2.0f,0.f), 0);
      fd2->shape = &bs2;
      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->density = 30.0;
      fd3->friction = 0.5;
      fd3->restitution = 0.f;
      fd3->shape = new b2PolygonShape;
      b2PolygonShape bs3;
      bs3.SetAsBox(0.2,2, b2Vec2(-2.0f,0.f), 0);
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
      bs4.SetAsBox(6,0.2, b2Vec2(24.f,-1.9f), 0);
      fd4->shape = &bs4;
      b2FixtureDef *fd5 = new b2FixtureDef;
      fd5->density = 10.0;
      fd5->friction = 0.5;
      fd5->restitution = 0.f;
      fd5->shape = new b2PolygonShape;
      b2PolygonShape bs5;
      bs5.SetAsBox(0.2,2, b2Vec2(29.0f,0.f), 0);
      fd5->shape = &bs5;
      b2FixtureDef *fd6 = new b2FixtureDef;
      fd6->density = 10.0;
      fd6->friction = 0.5;
      fd6->restitution = 0.f;
      fd6->shape = new b2PolygonShape;
      b2PolygonShape bs6;
      bs6.SetAsBox(0.2,2, b2Vec2(19.0f,0.f), 0);
      fd6->shape = &bs6;
       
      b2Body* box2 = m_world->CreateBody(bd);
      box2->CreateFixture(fd4);
      box2->CreateFixture(fd5);
      box2->CreateFixture(fd6);




      //The bar
      //bd->position.Set(10,15);	
      //fd1->density = 34.0;	  
      //b2Body* box2 = m_world->CreateBody(bd);
      //box2->CreateFixture(fd1);

      // The pulley joint
      b2PulleyJointDef* myjoint = new b2PulleyJointDef();
      b2Vec2 worldAnchorOnBody1(-10, 15); // Anchor point on body 1 in world axis
      b2Vec2 worldAnchorOnBody2(10, 26); // Anchor point on body 2 in world axis
      b2Vec2 worldAnchorGround1(-10, 20); // Anchor point for ground 1 in world axis
      b2Vec2 worldAnchorGround2(14, 20); // Anchor point for ground 2 in world axis
      float32 ratio = 1.0f; // Define ratio
      myjoint->Initialize(box1, box2, worldAnchorGround1, worldAnchorGround2, box1->GetWorldCenter(), box2->GetWorldCenter(), ratio);
      m_world->CreateJoint(myjoint);
    }


     //negative gravity balls
    {
      b2CircleShape shape;
     // shape.SetAsBox(0.1f, 1.0f);
      shape.m_radius=0.3f;
  
      b2FixtureDef fd;
      fd.shape = &shape;
      fd.density = 10.0f;
      fd.friction = 0.1f;
    
  {
    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.position.Set(24.0f + 0.5f, 1.0f);
    b2Body* body = m_world->CreateBody(&bd);
    body->SetGravityScale(-0.2);
    body->CreateFixture(&fd);
  }

  {
    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.position.Set(25.0f, 1.0f);
    b2Body* body = m_world->CreateBody(&bd);
    body->SetGravityScale(-0.2);
    body->CreateFixture(&fd);
  }

  {
    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.position.Set(24.0f - 0.5f, 1.0f);
    b2Body* body = m_world->CreateBody(&bd);
    body->SetGravityScale(-0.2);
    body->CreateFixture(&fd);
  }

  {
    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.position.Set(23.0f, 1.0f);
    b2Body* body = m_world->CreateBody(&bd);
    body->SetGravityScale(-0.2);
    body->CreateFixture(&fd);
  }
    }

    //The revolving horizontal platform
    {
      b2PolygonShape shape;
      shape.SetAsBox(4.0f, 0.2f);
	
      b2BodyDef bd;
      bd.position.Set(24.0f, -0.1f);
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
      bd2.position.Set(24.0f, 7.5f);
      b2Body* body2 = m_world->CreateBody(&bd2);

      b2RevoluteJointDef jointDef;
      jointDef.bodyA = body;
      jointDef.bodyB = body2;
      jointDef.localAnchorA.Set(0,0);
      jointDef.localAnchorB.Set(0,0);
      jointDef.collideConnected = false;
      m_world->CreateJoint(&jointDef);
    }


    //rod to restrict ballons
    {
      b2PolygonShape shape;
      shape.SetAsBox(0.1f, 10.0f);
	
      b2BodyDef bd;
      bd.position.Set(32.0f, 15.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }

    //right box to support table
    {
      b2PolygonShape shape;
      shape.SetAsBox(0.1f, 0.4f);
	
      b2BodyDef bd;
      bd.position.Set(28.5f, 22.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }

    //left box to support table
    {
      b2PolygonShape shape;
      shape.SetAsBox(0.1f, 0.4f);
	
      b2BodyDef bd;
      bd.position.Set(21.0f, 22.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }


// table
     {
      b2PolygonShape shape;
      shape.SetAsBox(5.0f, 0.1f);
	
      b2FixtureDef fd;
      fd.shape = &shape;
      fd.density = 2.0f;
      fd.friction = 0.1f;
	  b2BodyDef bd;
	  bd.type = b2_dynamicBody;
	  bd.position.Set(26.0f, 28.0f);
	  b2Body* body = m_world->CreateBody(&bd);
	  body->CreateFixture(&fd);
	} 


    //The heavy sphere on the platform
 /*   {
      b2Body* sbody;
      b2CircleShape circle;
      circle.m_radius = 1.0;
	
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 50.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
      b2BodyDef ballbd;
      ballbd.type = b2_dynamicBody;
      ballbd.position.Set(14.0f, 18.0f);
      sbody = m_world->CreateBody(&ballbd);
      sbody->CreateFixture(&ballfd);
    }
*/

    //The see-saw system at the bottom
 /*   {
      //The triangle wedge
      b2Body* sbody;
      b2PolygonShape poly;
      b2Vec2 vertices[3];
      vertices[0].Set(-1,0);
      vertices[1].Set(1,0);
      vertices[2].Set(0,1.5);
      poly.Set(vertices, 3);
      b2FixtureDef wedgefd;
      wedgefd.shape = &poly;
      wedgefd.density = 10.0f;
      wedgefd.friction = 0.0f;
      wedgefd.restitution = 0.0f;
      b2BodyDef wedgebd;
      wedgebd.position.Set(30.0f, 0.0f);
      sbody = m_world->CreateBody(&wedgebd);
      sbody->CreateFixture(&wedgefd);

      //The plank on top of the wedge
      b2PolygonShape shape;
      shape.SetAsBox(15.0f, 0.2f);
      b2BodyDef bd2;
      bd2.position.Set(30.0f, 1.5f);
      bd2.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd2);
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 1.f;
      fd2->shape = new b2PolygonShape;
      fd2->shape = &shape;
      body->CreateFixture(fd2);

      b2RevoluteJointDef jd;
      b2Vec2 anchor;
      anchor.Set(30.0f, 1.5f);
      jd.Initialize(sbody, body, anchor);
      m_world->CreateJoint(&jd);

      //The light box on the right side of the see-saw
      b2PolygonShape shape2;
      shape2.SetAsBox(2.0f, 2.0f);
      b2BodyDef bd3;
      bd3.position.Set(40.0f, 2.0f);
      bd3.type = b2_dynamicBody;
      b2Body* body3 = m_world->CreateBody(&bd3);
      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->density = 0.01f;
      fd3->shape = new b2PolygonShape;
      fd3->shape = &shape2;
      body3->CreateFixture(fd3);
    }
    */
  }

  sim_t *sim = new sim_t("Dominos", dominos_t::create);
}

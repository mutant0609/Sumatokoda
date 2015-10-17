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
#define DEGTORAD 0.01746
/**/
namespace cs251
{
  /**  The is the constructor
   * This is the documentation block for the constructor.
   */

  dominos_t::dominos_t()
  {
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

    //Motor
    {
    b2Body* motorpane;
    {
     b2PolygonShape shape;
     b2BodyDef bd;
     shape.SetAsBox(0.2f, 3.5f);
     bd.position.Set(2.0f, 32.5f);
     bd.type = b2_dynamicBody;
     motorpane = m_world->CreateBody(&bd);
     motorpane->CreateFixture(&shape, 0.5f);

    }
    b2Body* pin;
    {
     b2CircleShape cshape;
     b2BodyDef bd;
     cshape.m_radius = 0.4;
     bd.position.Set(2.0f, 32.5f);
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

	  ballbd.position.Set(-20.0f, 35.0f);
	  spherebody = m_world->CreateBody(&ballbd);
	  spherebody->CreateFixture(&ballfd);

    }
  // W 1st seg
     for(int i=0;i<7;i++)
    {
        b2Body* b2;
        b2PolygonShape shape;
        b2FixtureDef resti;
        resti.restitution=1.0;
        const b2Vec2 center((-20.0+1.0*i),(30.0-0.2*i*i));
        shape.SetAsBox(0.6+0.1*i, 0.1f,center,-1.0f);
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
        const b2Vec2 center((-1.0*i),(28.0-0.2*i*i));
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
        const b2Vec2 center((-9.0-1.2*i),(26.0-0.2*i*i));
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
        const b2Vec2 center((-10.0+1.2*i),(26.0-0.2*i*i));
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
        const b2Vec2 center((-14.0),(25.0));
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
        const b2Vec2 center((-6.0),(25.0));
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
        const b2Vec2 center((-20.0),(31.0));
        shape.SetAsBox(1.0, 0.1,center,-0.2f);
        b2BodyDef bd;
        b2 = m_world->CreateBody(&bd);
        b2->CreateFixture(&shape, 10.0f);
    }

{
        b2PolygonShape shape;
        const b2Vec2 center(45.0f, 41.0f);
        //center.Set(0.0f, 0.0f);
        shape.SetAsBox(2.0f, 0.1f,center,1.57f);

        b2BodyDef bd;
        //bd.position.Set(-31.0f, 30.0f);
        b2Body* ground = m_world->CreateBody(&bd);
        ground->CreateFixture(&shape, 0.0f);



    }

{
        b2PolygonShape shape;
        const b2Vec2 center(27.0f+10.0f, 14.0f);
        //center.Set(0.0f, 0.0f);
        shape.SetAsBox(2.0f, 0.1f,center,1.57f);

        b2BodyDef bd;
        //bd.position.Set(-31.0f, 30.0f);
        b2Body* ground = m_world->CreateBody(&bd);
        ground->CreateFixture(&shape, 0.0f);



    }


    {
        b2PolygonShape shape;
        const b2Vec2 center(27.0f+12.0f, 14.0f);
        //center.Set(0.0f, 0.0f);
        shape.SetAsBox(2.0f, 0.1f,center,1.57f);

        b2BodyDef bd;
        //bd.position.Set(-31.0f, 30.0f);
        b2Body* ground = m_world->CreateBody(&bd);
        ground->CreateFixture(&shape, 0.0f);



    }


    {
        b2PolygonShape shape;
        const b2Vec2 center(27.0f+17.5f, 22.5f);
        //center.Set(0.0f, 0.0f);
        shape.SetAsBox(10.0f, 0.10f,center,0.7f);

        b2BodyDef bd;
        //bd.position.Set(-31.0f, 30.0f);
        b2Body* ground = m_world->CreateBody(&bd);
        ground->CreateFixture(&shape, 0.0f);



    }
    /* Lower nozzle for wavy path */

    {
        b2PolygonShape shape;
        const b2Vec2 center(27.0f+22.0f, 24.5f);
        //center.Set(0.0f, 0.0f);
        shape.SetAsBox(13.0f, 0.10f,center,0.7f);

        b2BodyDef bd;
        //bd.position.Set(-31.0f, 30.0f);
        b2Body* ground = m_world->CreateBody(&bd);
        ground->CreateFixture(&shape, 0.0f);



    }

    {
        b2PolygonShape shape;
        const b2Vec2 center(27.0f+22.5f, 31.0f);
        //center.Set(0.0f, 0.0f);
        shape.SetAsBox(3.0f, 0.1f,center,-0.7f);

        b2BodyDef bd;
        //bd.position.Set(-31.0f, 30.0f);
        b2Body* ground = m_world->CreateBody(&bd);
        ground->CreateFixture(&shape, 0.0f);



    }
    /*Heavy ball*/
    {
      b2Body* spherebody;

      b2CircleShape circle;
      circle.m_radius = 0.4;

      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 80.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.1f;

	  b2BodyDef ballbd;
	  ballbd.type = b2_dynamicBody;
	  ballbd.position.Set(27.0f+22.0f, 33.0f);
	  spherebody = m_world->CreateBody(&ballbd);
	  spherebody->CreateFixture(&ballfd);

    }
    /*Cap for wavy path*/

    {
        b2PolygonShape shape;
        const b2Vec2 center(27.0f+18.0f, 33.0f);
        //center.Set(0.0f, 0.0f);
        shape.SetAsBox(0.1f, 2.0f,center,-1.57f);

        b2BodyDef bd;
        //bd.position.Set(-31.0f, 30.0f);
        b2Body* ground = m_world->CreateBody(&bd);
        ground->CreateFixture(&shape, 0.0f);



    }
    /*Lower balls container*/



     {
        b2PolygonShape shape;
        const b2Vec2 center(27.0f+14.0f, 8.0f);
        //center.Set(0.0f, 0.0f);
        shape.SetAsBox(0.1f, 3.0f,center,0.0f);

        b2BodyDef bd;
        //bd.position.Set(-31.0f, 30.0f);
        b2Body* ground = m_world->CreateBody(&bd);
        ground->CreateFixture(&shape, 0.0f);



    }
    /*Lower plank for box holding balls*/

     {
        b2PolygonShape shape;
        const b2Vec2 center(27.0f+11.0f, 5.0f);
        //center.Set(0.0f, 0.0f);
        shape.SetAsBox(3.0f, 0.1f,center,0.0f);

        b2BodyDef bd;
        //bd.position.Set(-31.0f, 30.0f);
        b2Body* ground = m_world->CreateBody(&bd);
        ground->CreateFixture(&shape, 0.0f);



    }
    /*Split for ball holding box*/
     {
        b2PolygonShape shape;
        const b2Vec2 center(27.0f+8.0f, 9.5f);
        //center.Set(0.0f, 0.0f);
        shape.SetAsBox(0.1f, 1.2f,center,0.0f);

        b2BodyDef bd;
        //bd.position.Set(-31.0f, 30.0f);
        b2Body* ground = m_world->CreateBody(&bd);
        ground->CreateFixture(&shape, 0.0f);



    }

     {
        b2PolygonShape shape;
        const b2Vec2 center(27.0f+8.0f, 5.5f);
        //center.Set(0.0f, 0.0f);
        shape.SetAsBox(0.1f, 0.5f,center,0.0f);

        b2BodyDef bd;
        //bd.position.Set(-31.0f, 30.0f);
        b2Body* ground = m_world->CreateBody(&bd);
        ground->CreateFixture(&shape, 0.0f);



    }
    /*Balls in container*/
    {
      b2Body* spherebody;

      b2CircleShape circle;
      circle.m_radius = 0.25;

      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 0.5f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
    for(int j=0;j<22;j++)
    {
      for (int i = 0; i < 9; ++i)
	{
	  b2BodyDef ballbd;
	  ballbd.type = b2_dynamicBody;
	  ballbd.position.Set(27.0f+(11.0+0.1*i), (8.0+0.01*j));
	  spherebody = m_world->CreateBody(&ballbd);
	  spherebody->CreateFixture(&ballfd);
	}
	}
    }
    /*channel system for balls*/

    {
        b2PolygonShape shape;
        const b2Vec2 center(27.0f+7.0f, 8.0f);
        //center.Set(0.0f, 0.0f);
        shape.SetAsBox(1.0f, 0.1f,center,0.0f);

        b2BodyDef bd;
        //bd.position.Set(-31.0f, 30.0f);
        b2Body* ground = m_world->CreateBody(&bd);
        ground->CreateFixture(&shape, 0.0f);
    }

     {
        b2PolygonShape shape;
        const b2Vec2 center(27.0f+7.0f, 6.0f);
        //center.Set(0.0f, 0.0f);
        shape.SetAsBox(1.0f, 0.1f,center,0.0f);

        b2BodyDef bd;
        //bd.position.Set(-31.0f, 30.0f);
        b2Body* ground = m_world->CreateBody(&bd);
        ground->CreateFixture(&shape, 0.0f);
    }

    /*part 2 of channel system*/
    /*split*/
    {
        b2PolygonShape shape;
        const b2Vec2 center(27.0f+6.0f, 9.5f);
        //center.Set(0.0f, 0.0f);
        shape.SetAsBox(0.1f, 1.5f,center,0.0f);

        b2BodyDef bd;
        //bd.position.Set(-31.0f, 30.0f);
        b2Body* ground = m_world->CreateBody(&bd);
        ground->CreateFixture(&shape, 0.0f);



    }
     {
        b2PolygonShape shape;
        const b2Vec2 center(27.0f+6.0f, 5.5f);
        //center.Set(0.0f, 0.0f);
        shape.SetAsBox(0.1f, 0.5f,center,0.0f);

        b2BodyDef bd;
        //bd.position.Set(-31.0f, 30.0f);
        b2Body* ground = m_world->CreateBody(&bd);
        ground->CreateFixture(&shape, 0.0f);



    }
    /*funnel*/
    {
    b2Body* gd;
    {
        b2PolygonShape shape;
        const b2Vec2 center(27.0f+4.0f, 11.0f);
        //center.Set(0.0f, 0.0f);
        shape.SetAsBox(2.0f, 0.1f,center,0.1f);

        b2BodyDef bd;
        //bd.position.Set(-31.0f, 30.0f);
        //b2Body* ground = m_world->CreateBody(&bd);
        gd = m_world->CreateBody(&bd);
        gd->CreateFixture(&shape, 0.0f);



    }
       }

    {
        b2PolygonShape shape;
        const b2Vec2 center(27.0f+3.0f, 10.0f);
        //center.Set(0.0f, 0.0f);
        shape.SetAsBox(1.0f, 0.1f,center,0.0f);

        b2BodyDef bd;
        //bd.position.Set(-31.0f, 30.0f);
        b2Body* ground = m_world->CreateBody(&bd);
        ground->CreateFixture(&shape, 0.0f);



    }
     {
        b2PolygonShape shape;
        const b2Vec2 center(27.0f+4.0f, 7.5f);
        //center.Set(0.0f, 0.0f);
        shape.SetAsBox(0.1f, 2.5f,center,0.0f);

        b2BodyDef bd;
        //bd.position.Set(-31.0f, 30.0f);
        b2Body* ground = m_world->CreateBody(&bd);
        ground->CreateFixture(&shape, 0.0f);



    }
    /*Lower plank for box holding balls*/

     {
        b2PolygonShape shape;
        const b2Vec2 center(27.0f+5.0f, 5.0f);
        //center.Set(0.0f, 0.0f);
        shape.SetAsBox(1.0f, 0.1f,center,0.0f);

        b2BodyDef bd;
        //bd.position.Set(-31.0f, 30.0f);
        b2Body* ground = m_world->CreateBody(&bd);
        ground->CreateFixture(&shape, 0.0f);



    }
    /*Heavy weight over balls*/
     {

        b2Body* wtbody;
        b2PolygonShape shape;
        //const b2Vec2 center(27.0f+11.0f, 11.0f);
        //center.Set(0.0f, 0.0f);
        shape.SetAsBox(2.9f, 0.5f);
        b2FixtureDef wtfd;
        wtfd.shape = &shape;
        wtfd.density = 1.0f;
        wtfd.friction = 0.0f;
        wtfd.restitution = 1.0f;
        b2BodyDef bd;
        bd.type=b2_dynamicBody;
        bd.position.Set(27.0f+11.0f, 11.0f);
        wtbody = m_world->CreateBody(&bd);
        wtbody->CreateFixture(&wtfd);
        //b2Body* ground = m_world->CreateBody(&bd);
        //ground->CreateFixture(&shape, 0.0f);
    }

    /*Platform for man*/

     {
        b2PolygonShape shape;
        const b2Vec2 center(27.0f+-3.0f, 5.0f);
        //center.Set(0.0f, 0.0f);
        shape.SetAsBox(3.5f, 1.0f,center,0.0f);

        b2BodyDef bd;
        //bd.position.Set(-31.0f, 30.0f);
        b2Body* ground = m_world->CreateBody(&bd);
        ground->CreateFixture(&shape, 0.0f);



    }
    /*dish*/
    /*Base of dish*/
     {
        b2PolygonShape shape;
        const b2Vec2 center(27.0f+-0.75f, 8.0f);
        //center.Set(0.0f, 0.0f);
        shape.SetAsBox(1.5f, 0.1f,center,0.0f);

        b2BodyDef bd;
        //bd.position.Set(-31.0f, 30.0f);
        b2Body* ground = m_world->CreateBody(&bd);
        ground->CreateFixture(&shape, 0.0f);



    }
    // slanting edges of dish
     {
        b2PolygonShape shape;
        const b2Vec2 center(27.0f+-2.2f, 9.1f);
        //center.Set(0.0f, 0.0f);
        shape.SetAsBox(1.2f, 0.1f,center,-1.1f);

        b2BodyDef bd;
        //bd.position.Set(-31.0f, 30.0f);
        b2Body* ground = m_world->CreateBody(&bd);
        ground->CreateFixture(&shape, 0.0f);



    }
     {
        b2PolygonShape shape;
        const b2Vec2 center(27.0f+1.0f, 9.1f);
        //center.Set(0.0f, 0.0f);
        shape.SetAsBox(1.0f, 0.1f,center,1.1f);

        b2BodyDef bd;
        //bd.position.Set(-31.0f, 30.0f);
        b2Body* ground = m_world->CreateBody(&bd);
        ground->CreateFixture(&shape, 0.0f);



    }
    /*Block below dish*/
     {
        b2PolygonShape shape;
        const b2Vec2 center(27.0f+-0.75f, 6.9f);
        //center.Set(0.0f, 0.0f);
        shape.SetAsBox(1.5f, 0.9f,center,0.0f);

        b2BodyDef bd;
        //bd.position.Set(-31.0f, 30.0f);
        b2Body* ground = m_world->CreateBody(&bd);
        ground->CreateFixture(&shape, 0.0f);



    }
    //man
     {
        b2PolygonShape shape;
        const b2Vec2 center(27.0f+-4.9f, 8.5f);
        //center.Set(0.0f, 0.0f);
        shape.SetAsBox(1.5f, 1.5f,center,0.0f);

        b2BodyDef bd;
        //bd.position.Set(-31.0f, 30.0f);
        b2Body* ground = m_world->CreateBody(&bd);
        ground->CreateFixture(&shape, 0.0f);



    }
    //man's legs

      {
        b2PolygonShape shape;
        const b2Vec2 center(27.0f+-5.1f, 6.5f);
        //center.Set(0.0f, 0.0f);
        shape.SetAsBox(0.1f, 0.5f,center,0.0f);

        b2BodyDef bd;
        //bd.position.Set(-31.0f, 30.0f);
        b2Body* ground = m_world->CreateBody(&bd);
        ground->CreateFixture(&shape, 0.0f);



    }

     {
        b2PolygonShape shape;
        const b2Vec2 center(27.0f+-4.6f, 6.5f);
        //center.Set(0.0f, 0.0f);
        shape.SetAsBox(0.1f, 0.5f,center,0.0f);

        b2BodyDef bd;
        //bd.position.Set(-31.0f, 30.0f);
        b2Body* ground = m_world->CreateBody(&bd);
        ground->CreateFixture(&shape, 0.0f);



    }

     {
      b2Body* spherebody;

      b2CircleShape circle;
      circle.m_radius = 1.0f;

      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 0.5f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
	  b2BodyDef ballbd;
	  ballbd.position.Set(27.0f+-4.9f, 11.0f);
	  spherebody = m_world->CreateBody(&ballbd);
	  spherebody->CreateFixture(&ballfd);
	}
 }
sim_t *sim = new sim_t("Dominos", dominos_t::create);
}




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

/**/
namespace cs251
{
  /**  The is the constructor
   * This is the documentation block for the constructor.
   */

  dominos_t::dominos_t()
  {
  // The ball
  {
      b2Body* spherebody;

      b2CircleShape circle;
      circle.m_radius = 0.4;

      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 80.0f;
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

  }



  sim_t *sim = new sim_t("Dominos", dominos_t::create);
}

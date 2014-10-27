// This file was part of the Irrlicht Engine's particle system, Copyright (C) 2002-2005 Nikolaus Gebhardt
// Adapted by Gaz Davidson - gaz at bitplane dot net

////////////////////////////////////////////////////////////////////////
// This node has been vastly improved from an old                     //
// scene node (by Bitplane) for use in the irrWeatherManager library. //
////////////////////////////////////////////////////////////////////////
// Josiah Hartzell - fighterstw@hotmail.com                           //
////////////////////////////////////////////////////////////////////////

#ifndef __C_CLOUD_NODE_INCLUDED__
#define __C_CLOUD_NODE_INCLUDED__

//#include "irrlicht.h"
#include <irrTypes.h>
#include <vector3d.h>
#include <irrArray.h>
#include <irrList.h>
#include <irrString.h>
#include <ISceneNode.h>
#include <S3DVertex.h>

#define CLOUD_PARTICLE_LIMIT 2000

namespace irr
{

class ITimer;

namespace scene
{

class IParticleAffector;


//! Struct for holding particle data
struct SCloudParticle
{
    //! Distance from camera
    u32 distance;

    //! Position of the particle, or position relative to parent cloud
    core::vector3d<f32> pos;

    //! Cloud size
    core::dimension2d<f32> size;

    //! Cloud colour - (tsk tsk, AmEn)
    video::SColor color;

    //! Number of children
    s16 children;

    //! Position of first child
    s16 firstchild;

    //! How much children will be scaled
    f32 childscale;
};





//! A particle system scene node.
class ICloudSceneNode : public ISceneNode
{
public:


    //! constructor
    ICloudSceneNode(
        ISceneNode* parent, ISceneManager* mgr, ITimer *devicetimer, s32 id,
        const core::vector3df& position,
        const core::vector3df& rotation,
        const core::vector3df& scale,
        f32 globParticleSize = 2000.0f);

    //! destructor
    virtual ~ICloudSceneNode();

    //! Adds new particle affector to the particle system.
    virtual void addAffector(IParticleAffector* affector);

    //! Removes all particle affectors in the particle system.
    virtual void removeAllAffectors();

    //! Returns the material based on the zero based index i.
    virtual video::SMaterial& getMaterial(u32 i);

    //! Returns amount of materials used by this scene node.
    virtual u32 getMaterialCount() const;

    //! pre render
    virtual void OnRegisterSceneNode();

    virtual void OnAnimate(irr::u32 timeMs);

    //! render
    virtual void render();

    //! returns the axis aligned bounding box of this node
    virtual const core::aabbox3d<f32>& getBoundingBox() const;

    // gets the current number of clouds on screen
    virtual s16 getCurrentCloudCount();

    //! cloud creation functions...
    virtual void makeRandomCloud(s16 count);

    //! turns z sorting on or off.
    //! speed increase for alpha blend clouds, or clouds that are one colour
    virtual void setZOrdering(bool zo);

    //! decides whether child nodes are the same colour as their parents
    virtual void setIgnoreChildColor(bool b);

    //! sets the maximum detail depth to draw
    virtual void setMaxDepth(s16 maxdepth);

    //! sets the level of detail ("distance/size" - scale of 1 to 10 works well)
    virtual void setLOD(f32 detail);

    //! sets if these clouds are sky clouds or local clouds
    //! if they are distant, factor says how they move in the distance (ie 0.1 = 10x)
    virtual void setSkyClouds(bool sky,f32 factor);

    //! sets the maximum time allowed to draw the screen.
    virtual void setMaxTimePerFrame(u32 t);

    //! Added for irrWeatherManager; Sets the scale of the entire cloud.
    virtual void setScale(const irr::core::vector3df &scale);

    int rand2(int lim, int seed);

    void setLightningHost(irr::f32 time) { isLightningHost = true; lightningEndTime = time; };

    void setDefaultColor(irr::video::SColor color) { DefaultColor = color; getMaterial(0).AmbientColor = DefaultColor; };

    void setCloudParticleSize(irr::f32 newSize) { cloudParticleSize = newSize; }


private:
    // functions
    void reallocateBuffers();
    void sortParticles();
    void makeParticles();
    s16 makeChildClouds(SCloudParticle &parent,s16 start,core::matrix4 &m, core::vector3df &campos );

    // shared variables
    core::array<SCloudParticle>      Particles; //
    core::array<video::S3DVertex>    Vertices; // 4 vertices per particle
    core::array<u16>                 Indices; // 6 indices per particle

    // instance variables
    core::list<IParticleAffector*>   AffectorList;


    core::array<SCloudParticle>      ParticleData;
    u32                              ParticleCount;
    u32                              ParticlesToDraw;

    u32                             depth; // for max depth

    bool                            ZOrdering;  // performance gain for fugly cloud
    bool                            SkyClouds; //
    f32                             SkyMoveFactor; //
    bool                            IgnoreChildColor;
    s16                             MaxDepth;
    f32                             LOD;

    ITimer                          *timer;
    u32                             MaxTimePerFrame;    // maximum time allowed to render
    u32                             lasttime;           // last time to draw frame
    u32                             lastcount;          // last number of polys

    video::SMaterial                Material;
    core::aabbox3d<f32>             Box;

    core::array<SCloudParticle*>    tmppointers;
    core::array<SCloudParticle>     tmpclouds;

    bool firstRun;

    f32 cloudParticleSize;

    bool isLightningHost;
    irr::f32 lightningEndTime;

    irr::video::SColor DefaultColor;

};

} // end namespace scene
} // end namespace irr


#endif

package com.networkController.util.physics;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.math.Rectangle;
import com.badlogic.gdx.math.Vector2;
import com.badlogic.gdx.physics.box2d.Body;
import com.badlogic.gdx.physics.box2d.BodyDef;
import com.badlogic.gdx.physics.box2d.FixtureDef;
import com.badlogic.gdx.physics.box2d.PolygonShape;
import com.badlogic.gdx.physics.box2d.World;
import com.badlogic.gdx.utils.Logger;

public class B2Model {
    public World world;
    private Body bodyd;
    private Body bodys;
    private Body bodyk;

    private Body rubber;
    private Body steel;
    private Body stone;
    private Body box;
    private Body player;


    private final Rectangle screenLeftSide;
    private final Rectangle screenRightSide;

    public boolean isSwimming = false;



    private static final Logger log = new Logger(B2Model.class.getName(), Logger.DEBUG);

    public B2Model(World world){
        //world = new World(new Vector2(0, -10), true);
        this.world = world;
        //this.world.setContactListener(new B2ContactListener());
        createFloor();




        float halfWorldWidth = Gdx.graphics.getWidth() / 2f;
        screenLeftSide = new Rectangle(0, 0, halfWorldWidth, Gdx.graphics.getHeight());
        screenRightSide = new Rectangle(halfWorldWidth, 0, halfWorldWidth, Gdx.graphics.getHeight());


        //TESTING BOX2D
        //createObject();
        //createMovingObject();
        /*
        BodyFactory bodyFactory = BodyFactory.getInstance(world);
        stone = bodyFactory.makeCirclePolyBody(1, 1, 2, BodyFactory.STONE, BodyDef.BodyType.DynamicBody, false);
        box = bodyFactory.makeBoxPolyBody(1.7f, 4, 1, 1, BodyFactory.STEEL, BodyDef.BodyType.StaticBody, false);
        bodyFactory.makeConeSensor(box, 1.5f);
        */

        // get our body factory singleton and store it in bodyFactory
        BodyFactory bodyFactory = BodyFactory.getInstance(world);
        rubber = bodyFactory.makeCirclePolyBody(2.7f, 7, 0.5f, BodyFactory.RUBBER, BodyDef.BodyType.DynamicBody, false);
        steel = bodyFactory.makeCirclePolyBody(1.5f, 8, 1, BodyFactory.STEEL, BodyDef.BodyType.DynamicBody, false);

        // add a player
        player = bodyFactory.makeBoxPolyBody(4, 4, 2, 2, BodyFactory.WOOD, BodyDef.BodyType.DynamicBody,false);

        // add some water
        //Body water =  bodyFactory.makeBoxPolyBody(1, 1.5f, 40, 4, BodyFactory.RUBBER, BodyDef.BodyType.StaticBody,false);
        // make the water a sensor so it doesn't obstruct our player
        //bodyFactory.makeAllFixturesSensors(water);
        //water.setUserData("IAMTHESEA");

    }

    private void createFloor() {

        // create a new body definition (type and location)
        BodyDef bodyDef = new BodyDef();
        bodyDef.type = BodyDef.BodyType.StaticBody;
        bodyDef.position.set(0, -1);

        // add it to the world
        bodyd = world.createBody(bodyDef);

        // set the shape (here we use a box 50 meters wide, 1 meter tall )
        PolygonShape shape = new PolygonShape();
        shape.setAsBox(50, 1);

        // create the physical object in our body)
        // without this our body would just be data in the world
        bodyd.createFixture(shape, 0.0f);

        // we no longer use the shape object here so dispose of it.
        shape.dispose();
    }

    private void createObject(){

        //create a new body definition (type and location)
        BodyDef bodyDef = new BodyDef();
        bodyDef.type = BodyDef.BodyType.DynamicBody;
        bodyDef.position.set(5,4);


        // add it to the world
        bodys = world.createBody(bodyDef);

        // set the shape (here we use a box 50 meters wide, 1 meter tall )
        PolygonShape shape = new PolygonShape();
        shape.setAsBox(1,1);

        // set the properties of the object ( shape, weight, restitution(bouncyness)
        FixtureDef fixtureDef = new FixtureDef();
        fixtureDef.shape = shape;
        fixtureDef.density = 1f;

        // create the physical object in our body)
        // without this our body would just be data in the world
        bodys.createFixture(shape, 0.0f);

        // we no longer use the shape object here so dispose of it.
        shape.dispose();
    }

    private void createMovingObject(){

        //create a new body definition (type and location)
        BodyDef bodyDef = new BodyDef();
        bodyDef.type = BodyDef.BodyType.KinematicBody;
        bodyDef.position.set(2.5f,-12.0f);


        // add it to the world
        bodyk = world.createBody(bodyDef);

        // set the shape (here we use a box 50 meters wide, 1 meter tall )
        PolygonShape shape = new PolygonShape();
        shape.setAsBox(1,1);

        // set the properties of the object ( shape, weight, restitution(bouncyness)
        FixtureDef fixtureDef = new FixtureDef();
        fixtureDef.shape = shape;
        fixtureDef.density = 1f;

        // create the physical object in our body)
        // without this our body would just be data in the world
        bodyk.createFixture(shape, 0.0f);

        // we no longer use the shape object here so dispose of it.
        shape.dispose();

        bodyk.setLinearVelocity(0, 0.75f);
        //bodyk.setLinearVelocity(0, 0.75f);
    }


    public void update(float delta){


            if (Gdx.input.isTouched()) {
                float screenX = Gdx.input.getX(); // in pixels
                float screenY = Gdx.input.getY(); // in pixels

                Vector2 screenCoordinates = new Vector2(screenX, screenY); // in pixels
                //Vector2 worldCoordinates = controller.screenToWorld(screenCoordinates); // world units
                Vector2 worldCoordinates = new Vector2(Gdx.graphics.getWidth(), Gdx.graphics.getHeight()); // world units

                if (screenX < Gdx.graphics.getWidth()/2 &&
                    screenY > Gdx.graphics.getHeight() - Gdx.graphics.getHeight()/8) {
                //if (screenX < 440) {
                //if (isLeftSideTouched(worldCoordinates)) {
                    player.setLinearVelocity(new Vector2(-1.0f, player.getLinearVelocity().y));
                }
                else if (screenX > Gdx.graphics.getWidth()/2 &&
                    screenY > Gdx.graphics.getHeight() - Gdx.graphics.getHeight()/8) {
                //else if (screenX > 440) {
                //} else if (isRightSideTouched(worldCoordinates)) {
                    player.setLinearVelocity(new Vector2(1.0f, player.getLinearVelocity().y));
                }
                //else
                    //player.setLinearVelocity(new Vector2(0.0f, 0.0f));

                System.out.println("Player pos - x:" + player.getPosition().x + ", y:" + player.getPosition().y);
                //System.out.println("Touch X: " + screenX + "\nTouch Y:" + screenY);
            }



        if(isSwimming)
            player.applyForceToCenter(0, 50, true);
        world.step(delta, 3, 3);
        //log.debug("BOX2D - POS: " + bodyk.getPosition().x + " , " + bodyk.getPosition().y );
    }


    // == private methods ==
    private boolean isLeftSideTouched(Vector2 worldCoordinates) {
        return screenLeftSide.contains(worldCoordinates);
    }

    private boolean isRightSideTouched(Vector2 worldCoordinates) {
        return screenRightSide.contains(worldCoordinates);
    }
}

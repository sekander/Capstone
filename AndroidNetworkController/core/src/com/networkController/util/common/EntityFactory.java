package com.networkController.util.common;

import com.networkController.util.assets.AssetDescriptors;
import com.networkController.util.components.B2BodyComponent;
import com.networkController.util.components.MovementComponent;
import com.networkController.util.components.ParallaxComponenet;
import com.networkController.util.components.PlayerComponent;
import com.networkController.util.components.TextureComponent;
import com.networkController.util.components.TransformComponent;
import com.badlogic.ashley.core.Entity;
import com.badlogic.ashley.core.PooledEngine;
import com.badlogic.gdx.assets.AssetManager;
import com.badlogic.gdx.physics.box2d.BodyDef;
import com.networkController.util.physics.BodyFactory;

public class EntityFactory {

    private final PooledEngine engine;
    private final AssetManager assetManager;
    private final BodyFactory bodyFactory;


    public EntityFactory(PooledEngine engine, AssetManager assetManager, BodyFactory bodyFactory) {
        this.engine = engine;
        this.assetManager = assetManager;
        this.bodyFactory = bodyFactory;
    }

    public void addPlayer(float xpos, float ypos, float width, float height){
        Entity entity = engine.createEntity();


        TransformComponent tranform = engine.createComponent(TransformComponent.class);
        tranform.position.x = xpos;
        tranform.position.y = ypos;

        PlayerComponent player = engine.createComponent(PlayerComponent.class);

        TextureComponent texture = engine.createComponent(TextureComponent.class);
        texture.texture = assetManager.get(AssetDescriptors.PLAYER);
        texture.width = width;
        texture.height = height;

        B2BodyComponent b2dbody = engine.createComponent(B2BodyComponent.class);
        b2dbody.body = bodyFactory.makeBoxPolyBody(tranform.position.x, tranform.position.y,
                texture.width, texture.height, BodyFactory.STONE, BodyDef.BodyType.DynamicBody, true);
        b2dbody.body.setUserData(entity);

        //Entity Components
        entity.add(tranform);
        entity.add(player);
        entity.add(texture);
        entity.add(b2dbody);

        //Add entity
        engine.addEntity(entity);

    }

    public void addBackground(String fileName, int x, int y, float width, float height){
        TextureComponent texture = engine.createComponent(TextureComponent.class);
        //texture.texture = assetManager.get(AssetDescriptors.BACKGROUND);
        texture.texture = assetManager.get(fileName);
        texture.width = width;
        texture.height = height;

        TransformComponent transform = engine.createComponent(TransformComponent.class);
        transform.position.x = x;
        transform.position.y = y;

        Entity entity = engine.createEntity();
        entity.add(texture);
        entity.add(transform);

        engine.addEntity(entity);
    }


    public void addParallax(String fileName, int x, int y, float width, float height){
        TextureComponent texture = engine.createComponent(TextureComponent.class);
        //texture.texture = assetManager.get(AssetDescriptors.BACKGROUND);
        texture.texture = assetManager.get(fileName);
        texture.width = width;
        texture.height = height;

        TransformComponent transform = engine.createComponent(TransformComponent.class);
        transform.position.x = x;
        transform.position.y = y;

        MovementComponent movement = engine.createComponent(MovementComponent.class);
        ParallaxComponenet parallax = engine.createComponent(ParallaxComponenet.class);

        //B2BodyComponent b2dbody = engine.createComponent(B2BodyComponent.class);
        //b2dbody.body = bodyFactory.makeBoxPolyBody(x, y, 3, 0.2f, BodyFactory.STONE, BodyDef.BodyType.StaticBody, true);


        Entity entity = engine.createEntity();
        entity.add(movement);
        entity.add(parallax);
        entity.add(texture);
        entity.add(transform);

        engine.addEntity(entity);


    }

    public void addFloor(){
        Entity entity = engine.createEntity();
        B2BodyComponent b2dbody = engine.createComponent(B2BodyComponent.class);
        b2dbody.body = bodyFactory.makeBoxPolyBody(0, 10, 1000, 0.2f, BodyFactory.STONE, BodyDef.BodyType.StaticBody, true);
        B2BodyComponent testbody = engine.createComponent(B2BodyComponent.class);
        testbody.body = bodyFactory.makeBoxPolyBody(1, 50, 10, 10, BodyFactory.RUBBER, BodyDef.BodyType.DynamicBody, true);
        /*
        TextureComponent texture = engine.createComponent(TextureComponent.class);
        texture.region = atlas.findRegion("player");
        TypeComponent type = engine.createComponent(TypeComponent.class);
        type.type = TypeComponent.SCENERY;
        */

        b2dbody.body.setUserData(entity);

        entity.add(b2dbody);
        entity.add(testbody);
        //entity.add(texture);
        //entity.add(type);

        engine.addEntity(entity);
    }


}

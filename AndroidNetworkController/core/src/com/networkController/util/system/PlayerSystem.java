package com.networkController.util.system;

import com.networkController.util.components.B2BodyComponent;
import com.networkController.util.components.PlayerComponent;
import com.badlogic.ashley.core.ComponentMapper;
import com.badlogic.ashley.core.Entity;
import com.badlogic.ashley.core.Family;
import com.badlogic.ashley.systems.IteratingSystem;
import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.Input;
import com.badlogic.gdx.graphics.OrthographicCamera;
import com.badlogic.gdx.math.Vector2;
import com.networkController.util.controller.GamePAD;

public class PlayerSystem extends IteratingSystem {

    private GamePAD gamePAD;
    private final OrthographicCamera camera;
    float x, y;

    ComponentMapper<PlayerComponent> pComp;
    ComponentMapper<B2BodyComponent> bComp;

    public PlayerSystem(GamePAD gamePAD, OrthographicCamera camera) {
    //public PlayerSystem(GamePAD gamePAD) {
        super(Family.all(PlayerComponent.class).get());
        this.gamePAD = gamePAD;
        this.camera = camera;
        pComp = ComponentMapper.getFor(PlayerComponent.class);
        bComp = ComponentMapper.getFor(B2BodyComponent.class);
    }

    @Override
    protected void processEntity(Entity entity, float deltaTime) {
        B2BodyComponent b2Body = bComp.get(entity);
        pComp.get(entity).xpos = b2Body.body.getPosition().x;
        pComp.get(entity).ypos = b2Body.body.getPosition().y;


        //System.out.println("Camera x pos : " + camera.position.x);
        //camera.position.x = Math.round(pComp.get(entity).xpos * 100)/100;
        //camera.position.x = b2Body.body.getPosition().x;
        //camera.position.x = b2Body.body.getPosition().x;
        camera.position.x = 20.0f * deltaTime ;
        //camera.position.x = b2Body.body.getLinearVelocity().x * deltaTime * 10;
        //camera.position.x = b2Body.body.getLinearVelocity().x*deltaTime;





        if(Gdx.input.isKeyPressed(Input.Keys.RIGHT))
            b2Body.body.setLinearVelocity( 1.0f, 0);
        else if (Gdx.input.isKeyPressed(Input.Keys.LEFT))
            b2Body.body.setLinearVelocity( -1.0f, 0);

        if(gamePAD.getMarkedCurrentController() != null) {
            if (gamePAD.getMarkedCurrentController().getButton(gamePAD.getMarkedCurrentController().getMapping().buttonDpadUp))
                b2Body.body.setLinearVelocity( 1.0f, 0);
            else if (gamePAD.getMarkedCurrentController().getButton(gamePAD.getMarkedCurrentController().getMapping().buttonDpadDown))
                b2Body.body.setLinearVelocity( -1.0f, 0);
        }
        //Add touch screen controls


        if (Gdx.input.isTouched()) {
            float screenX = Gdx.input.getX(); // in pixels
            float screenY = Gdx.input.getY(); // in pixels

            x = Gdx.input.getX() - 1 - x;
            y = Gdx.input.getY() - 1 - y;


            if (screenX < Gdx.graphics.getWidth()/2 &&
                    screenY > Gdx.graphics.getHeight() - Gdx.graphics.getHeight()/8) {
                b2Body.body.setLinearVelocity(new Vector2(-1.0f, b2Body.body.getLinearVelocity().y));
            }
            else if (screenX > Gdx.graphics.getWidth()/2 && screenY > Gdx.graphics.getHeight() - Gdx.graphics.getHeight()/8) {
                b2Body.body.setLinearVelocity(new Vector2(1.0f, b2Body.body.getLinearVelocity().y));
            }
            else if(screenX < Gdx.graphics.getWidth()/2 &&
                    screenY > Gdx.graphics.getHeight()/2 &&
                    screenY < Gdx.graphics.getHeight() - Gdx.graphics.getHeight()/8) {
                b2Body.body.setLinearVelocity(new Vector2(b2Body.body.getLinearVelocity().x - 1.0f,
                        5.f));
            }
            else if(screenX > Gdx.graphics.getWidth()/2 &&
                    screenY > Gdx.graphics.getHeight()/2 &&
                    screenY < Gdx.graphics.getHeight() - Gdx.graphics.getHeight()/8) {
                b2Body.body.setLinearVelocity(new Vector2(b2Body.body.getLinearVelocity().x + 1.0f,
                        5.f));
            }
            else if(screenY < Gdx.graphics.getHeight()/2)
                b2Body.body.setLinearVelocity(new Vector2(b2Body.body.getLinearVelocity().x,
                        50.0f));
        }
    }
}

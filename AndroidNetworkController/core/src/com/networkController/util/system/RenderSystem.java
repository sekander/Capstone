package com.networkController.util.system;

import com.networkController.util.common.Mappers;
import com.networkController.util.components.B2BodyComponent;
import com.networkController.util.components.TextureComponent;
import com.networkController.util.components.TransformComponent;
import com.badlogic.ashley.core.ComponentMapper;
import com.badlogic.ashley.core.Entity;
import com.badlogic.ashley.core.EntitySystem;
import com.badlogic.ashley.core.Family;
import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;
import com.badlogic.gdx.math.Vector2;
import com.badlogic.gdx.utils.viewport.Viewport;

public class RenderSystem extends EntitySystem {
    private static final Family FAMILY = Family.all(
            TextureComponent.class,
            //B2BodyComponent.class,

            TransformComponent.class
    ).get();

    private final Viewport viewport;
    private final SpriteBatch batch;
    ComponentMapper<B2BodyComponent> bComp;


    public RenderSystem(Viewport viewport, SpriteBatch batch) {
        this.viewport = viewport;
        this.batch = batch;
        bComp = ComponentMapper.getFor(B2BodyComponent.class);
        //ImmutableArray<Entity> entities = getEngine().getEntitiesFor(FAMILY);
        //renderQueue.addAll(entities.toArray());
    }

    @Override
    public void update(float deltaTime) {

        viewport.apply();
        batch.setProjectionMatrix(viewport.getCamera().combined);
        batch.begin();

            draw();

        batch.end();
    }

    private void draw() {
        //for(Entity entity : renderQueue)
        for(Entity entity : getEngine().getEntitiesFor(FAMILY))
        {
            TransformComponent transform = Mappers.TRANSFORM.get(entity);
            TextureComponent texture = Mappers.TEXTURE.get(entity);
            B2BodyComponent b2Body = bComp.get(entity);

            if(texture != null)
                batch.draw(texture.texture,
                            //b2Body.body.getPosition().x,
                            //b2Body.body.getPosition().y,
                            transform.position.x  - texture.width/2,
                            transform.position.y - texture.height/2,
                            texture.width,
                            texture.height);
                //batch.draw()
        }
    }


    static final float PPM = 32.0f; // sets the amount of pixels each metre of box2d objects contains

    // this gets the height and width of our camera frustrum based off the width and height of the screen and our pixel per meter ratio
    static final float FRUSTUM_WIDTH = Gdx.graphics.getWidth()/PPM;
    static final float FRUSTUM_HEIGHT = Gdx.graphics.getHeight()/PPM;

    public static final float PIXELS_TO_METRES = 1.0f / PPM; // get the ratio for converting pixels to metres

    // static method to get screen width in metres
    private static Vector2 meterDimensions = new Vector2();
    private static Vector2 pixelDimensions = new Vector2();
    public static Vector2 getScreenSizeInMeters(){
        meterDimensions.set(Gdx.graphics.getWidth()*PIXELS_TO_METRES,
                Gdx.graphics.getHeight()*PIXELS_TO_METRES);
        return meterDimensions;
    }

    // static method to get screen size in pixels
    public static Vector2 getScreenSizeInPixesl(){
        pixelDimensions.set(Gdx.graphics.getWidth(), Gdx.graphics.getHeight());
        return pixelDimensions;
    }

    // convenience method to convert pixels to meters
    public static float PixelsToMeters(float pixelValue){
        return pixelValue * PIXELS_TO_METRES;
    }

}

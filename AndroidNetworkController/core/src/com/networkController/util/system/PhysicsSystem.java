package com.networkController.util.system;

import com.networkController.util.components.B2BodyComponent;
import com.networkController.util.components.TransformComponent;
import com.badlogic.ashley.core.ComponentMapper;
import com.badlogic.ashley.core.Entity;
import com.badlogic.ashley.core.Family;
import com.badlogic.ashley.systems.IteratingSystem;
import com.badlogic.gdx.math.MathUtils;
import com.badlogic.gdx.math.Vector2;
import com.badlogic.gdx.physics.box2d.World;
import com.badlogic.gdx.utils.Array;

public class PhysicsSystem extends IteratingSystem {
    private static final float MAX_STEP_TIME = 1/45f;
    private static float accumulator = 0f;

    private World world;
    private Array<Entity> bodiesQueue;

    private ComponentMapper<B2BodyComponent> bComp = ComponentMapper.getFor(B2BodyComponent.class);
    private ComponentMapper<TransformComponent> tComp = ComponentMapper.getFor(TransformComponent.class);

    @SuppressWarnings("unchecked")
    public PhysicsSystem(World world) {
        super(Family.all(B2BodyComponent.class, TransformComponent.class).get());
        this.world = world;
        this.bodiesQueue = new Array<Entity>();
    }

    @Override
    public void update(float deltaTime) {
        super.update(deltaTime);
        float frameTime = Math.min(deltaTime, 0.25f);
        accumulator += frameTime;
        if(accumulator >= MAX_STEP_TIME) {
            world.step(MAX_STEP_TIME, 6, 2);
            accumulator -= MAX_STEP_TIME;

            //Entity Queue
            for (Entity entity : bodiesQueue) {
                TransformComponent transform = tComp.get(entity);
                B2BodyComponent bodyComp = bComp.get(entity);
                Vector2 position = bodyComp.body.getPosition();
                transform.position.x = position.x;
                transform.position.y = position.y;
                transform.rotation = bodyComp.body.getAngle() * MathUtils.radiansToDegrees;
            }
        }
        bodiesQueue.clear();
    }

    @Override
    protected void processEntity(Entity entity, float deltaTime) {
        bodiesQueue.add(entity);
    }

}

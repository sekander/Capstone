package com.networkController.util.system;

import com.networkController.util.common.Mappers;
import com.networkController.util.components.MovementComponent;
import com.networkController.util.components.ParallaxComponenet;
import com.networkController.util.components.TransformComponent;
import com.badlogic.ashley.core.Entity;
import com.badlogic.ashley.core.Family;
import com.badlogic.ashley.systems.IteratingSystem;

public class ParallaxSystem extends IteratingSystem {
    public static final Family FAMILY = Family.all(
            TransformComponent.class,
            MovementComponent.class,
            ParallaxComponenet.class
    ).get();

    public ParallaxSystem(){super((FAMILY));}


    @Override
    protected void processEntity(Entity entity, float deltaTime) {
        TransformComponent transform = Mappers.TRANSFORM.get(entity);
        MovementComponent movement = Mappers.MOVEMENT.get(entity);
        ParallaxComponenet parallax = Mappers.PARALLAX.get(entity);
        //ParallaxComponenet parallax = Mappers.

        movement.ySpeed = -0.01f;

        if(transform.y < -10.0f)
            transform.y = 0;
    }
}

package com.networkController.util.common;

import com.networkController.util.components.BoundsComponent;
import com.networkController.util.components.MovementComponent;
import com.networkController.util.components.ObstacleComponent;
import com.networkController.util.components.ParallaxComponenet;
import com.networkController.util.components.TextureComponent;
import com.networkController.util.components.TransformComponent;
import com.badlogic.ashley.core.ComponentMapper;

public class Mappers {

    public static final ComponentMapper<BoundsComponent> BOUNDS =
            ComponentMapper.getFor(BoundsComponent.class);

    public static final ComponentMapper<MovementComponent> MOVEMENT =
            ComponentMapper.getFor(MovementComponent.class);

    public static final ComponentMapper<TransformComponent> TRANSFORM =
            ComponentMapper.getFor(TransformComponent.class);

    public static final ComponentMapper<ObstacleComponent> OBSTACLE =
            ComponentMapper.getFor(ObstacleComponent.class);

    public static final ComponentMapper<TextureComponent> TEXTURE =
            ComponentMapper.getFor(TextureComponent.class);

    public static final ComponentMapper<ParallaxComponenet> PARALLAX =
            ComponentMapper.getFor(ParallaxComponenet.class);

    private Mappers(){}
}

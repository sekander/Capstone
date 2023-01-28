package com.networkController.util.debug;

import com.badlogic.gdx.graphics.glutils.ShapeRenderer;
import com.badlogic.gdx.math.Circle;
import com.badlogic.gdx.math.Polygon;
import com.badlogic.gdx.math.Rectangle;
import com.networkController.util.Validate;

public class ShapeRendererUtils {
    // == constructors ==
    private ShapeRendererUtils() {
    }

    // == public methods ==
    public static void rect(ShapeRenderer renderer, Rectangle rectangle) {
        // validating parameters
        Validate.notNull(renderer);
        Validate.notNull(rectangle);

        renderer.rect(rectangle.x, rectangle.y, rectangle.width, rectangle.height);
    }

    public static void circle(ShapeRenderer renderer, Circle circle) {
        // validate params
        Validate.notNull(renderer);
        Validate.notNull(circle);

        renderer.circle(circle.x, circle.y, circle.radius, 15);
    }

    public static void polygon(ShapeRenderer renderer, Polygon polygon) {
        // validate params
        Validate.notNull(renderer);
        Validate.notNull(polygon);

        renderer.polygon(polygon.getTransformedVertices());
    }

}

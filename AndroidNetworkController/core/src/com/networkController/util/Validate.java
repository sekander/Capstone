package com.networkController.util;

public class Validate {
    // == constants ==
    private static final String DEFAULT_IS_NULL_MESSAGE = "The validated objectis null.";

    // == constructors ==
    private Validate() {
    }

    // == public methods ==
    public static <T> void notNull(T object) {
        notNull(object, DEFAULT_IS_NULL_MESSAGE);
    }

    public static <T> void notNull(T object, String message) {
        if (object == null) {
            throw new NullPointerException(message);
        }
    }

}

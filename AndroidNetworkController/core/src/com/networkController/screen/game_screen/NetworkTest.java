package com.networkController.screen.game_screen;

import com.badlogic.ashley.core.PooledEngine;
import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.Net;
import com.badlogic.gdx.assets.AssetManager;
import com.badlogic.gdx.graphics.Color;
import com.badlogic.gdx.graphics.GL20;
import com.badlogic.gdx.graphics.OrthographicCamera;
import com.badlogic.gdx.graphics.g2d.BitmapFont;
import com.badlogic.gdx.graphics.g2d.GlyphLayout;
import com.badlogic.gdx.graphics.g2d.freetype.FreeTypeFontGenerator;
import com.badlogic.gdx.graphics.glutils.ShapeRenderer;
import com.badlogic.gdx.math.Matrix4;
import com.badlogic.gdx.math.Vector2;
import com.badlogic.gdx.math.Vector3;
import com.badlogic.gdx.net.Socket;
import com.badlogic.gdx.net.SocketHints;
import com.badlogic.gdx.utils.ScreenUtils;
import com.badlogic.gdx.utils.viewport.FitViewport;
import com.badlogic.gdx.utils.viewport.Viewport;
import com.networkController.util.assets.AssetDescriptors;
import com.networkController.util.common.EntityFactory;
import com.networkController.util.game.GameBase;
import com.networkController.util.screen.ScreenBaseAdapter;
import com.networkController.util.system.HudRenderSystem;
import com.networkController.util.system.RenderSystem;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class NetworkTest extends ScreenBaseAdapter {

    private final GameBase game;
    private final AssetManager assetManager;

    private OrthographicCamera camera;
    private Viewport viewport;

    private PooledEngine engine;
    private EntityFactory factory;
    BitmapFont font;
    GlyphLayout layout;

    private  String testingString;
    private String response;

    SocketHints hints = new SocketHints();
    //SocketHints hints;
    Socket client = Gdx.net.newClientSocket(Net.Protocol.TCP, "192.168.0.102", 8080, hints);
    //Socket client = Gdx.net.newClientSocket(Net.Protocol.TCP, "192.168.5.230", 8080, hints);
    //Socket client;

    private Matrix4 oldTransformMatrix;
    Matrix4 mx4Font = new Matrix4();



    private ShapeRenderer debugRender;
    public NetworkTest(GameBase game){
        this.game = game;
        this.assetManager = game.getAssetManager();
    }

    @Override
    public void show() {

        //hints = new SocketHints();
        //client = Gdx.net.newClientSocket(Net.Protocol.TCP, "192.168.0.102", 8080, hints);
        camera = new OrthographicCamera();
        viewport = new FitViewport(Gdx.graphics.getWidth()/10, Gdx.graphics.getHeight()/10, camera);
        debugRender = new ShapeRenderer();

        oldTransformMatrix = game.getBatch().getTransformMatrix().cpy();

        layout = new GlyphLayout();
        FreeTypeFontGenerator generator = new FreeTypeFontGenerator(Gdx.files.internal("ui/fonts/Minecraft.ttf"));
        FreeTypeFontGenerator.FreeTypeFontParameter parameter = new FreeTypeFontGenerator.FreeTypeFontParameter();
        parameter.size = 20;

        font = assetManager.get(AssetDescriptors.FONT);
        font.getData().setScale(0.5f, 0.5f);

        //font = assetManager.get(AssetDescriptors.DEFAULT_FONT);
        font = generator.generateFont(parameter);
        //font = assetManager.get(String.valueOf(Gdx.files.internal("ui_font_32.fnt")));
        oldTransformMatrix.setToRotation(new Vector3(0, 0, 1), 90);

        //Entity System
        engine = new PooledEngine();
        engine.addSystem(new RenderSystem(viewport, game.getBatch()));
        engine.addSystem(new HudRenderSystem(viewport, game.getBatch(), font ));
        factory = new EntityFactory(engine, assetManager, null);

        testingString = "Testing!!!";

        new Thread(new Runnable() {
            @Override
            public void run() {
                //while(true) {
                    System.out.println("Thread Loop");

                    try {
                        while(true) {

                            client.getOutputStream().write("Android Phone\n".getBytes());
                            response = new BufferedReader(new InputStreamReader(client.getInputStream())).readLine();
                            //response = new BufferedReader(new InputStreamReader(client.getInputStream())).readLine();

                            Gdx.app.log("AndroidNetworkController", "got server message: " + response);
                            System.out.println("Server Messager : " + response);
                        }
                    } catch (IOException e) {
                        Gdx.app.log("AndroidNetworkController", "an error occured", e);
                    }
               // }
            }
        }).start();



    }

    @Override
    public void render(float delta) {
        ScreenUtils.clear(Color.BLACK);
        //System.out.println("Main Thread!!!");
        //System.out.println("Server Messager : " + response);

        Gdx.gl.glEnable(GL20.GL_BLEND);
        Gdx.gl.glBlendFunc(GL20.GL_SRC_ALPHA, GL20.GL_ONE_MINUS_SRC_ALPHA);
        //Update time
        //GameManager.INSTANCE.setGameTime(updatedTime);
        //
        //game.getBatch().setTransformMatrix(oldTransformMatrix);


        game.getBatch().enableBlending();

        DrawDebugLine(new Vector2(0, 225), new Vector2(108, 225), 2, Color.RED, camera.combined);
        DrawDebugLine(new Vector2(0, 129), new Vector2(108, 129), 2, Color.BLUE, camera.combined);
        DrawDebugLine(new Vector2(54, 225), new Vector2(54, 33), 2, Color.GREEN, camera.combined);
        DrawDebugLine(new Vector2(0, 33), new Vector2(108, 33), 2, Color.RED, camera.combined);


        game.getBatch().begin();
        //layout.setText(font, testingString);
        //layout.setText(font, response);
        //font.draw(game.getBatch(), testingString, 20, 100);
            //font.draw(game.getBatch(), layout, 20, 100);
        if(response != null)

            font.draw(game.getBatch(), response, 20, 100);
        game.getBatch().end();

        engine.update(delta);
    }

    @Override
    public void resize(int width, int height) {
        viewport.update(width, height, true);
    }

    @Override
    public void pause() {
        super.pause();
    }

    @Override
    public void resume() {
        super.resume();
    }

    @Override
    public void hide() {
        super.hide();
    }

    @Override
    public void dispose() {
        super.dispose();
    }

    public void DrawDebugLine(Vector2 start, Vector2 end, int lineWidth, Color color, Matrix4 projectionMatrix)
    {
        Gdx.gl.glLineWidth(lineWidth);
        debugRender.setProjectionMatrix(projectionMatrix);
        debugRender.begin(ShapeRenderer.ShapeType.Line);
        debugRender.setColor(color);
        debugRender.line(start, end);
        debugRender.end();
        Gdx.gl.glLineWidth(1);
    }
}

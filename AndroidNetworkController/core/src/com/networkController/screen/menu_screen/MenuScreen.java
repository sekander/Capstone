package com.networkController.screen.menu_screen;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.InputProcessor;
import com.badlogic.gdx.assets.AssetManager;
import com.badlogic.gdx.graphics.Color;
import com.badlogic.gdx.graphics.Pixmap;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.g2d.Batch;
import com.badlogic.gdx.graphics.g2d.BitmapFont;
import com.badlogic.gdx.graphics.g2d.freetype.FreeTypeFontGenerator;
import com.badlogic.gdx.scenes.scene2d.Actor;
import com.badlogic.gdx.scenes.scene2d.Stage;
import com.badlogic.gdx.scenes.scene2d.ui.Skin;
import com.badlogic.gdx.scenes.scene2d.ui.Table;
import com.badlogic.gdx.scenes.scene2d.ui.TextButton;
import com.badlogic.gdx.scenes.scene2d.utils.ChangeListener;
import com.badlogic.gdx.utils.viewport.FitViewport;
import com.badlogic.gdx.utils.viewport.Viewport;
import com.networkController.screen.game_screen.NetworkTest;
import com.networkController.screen.transition.ScreenTransitions;
import com.networkController.util.GdxUtils;
import com.networkController.util.assets.AssetDescriptors;
import com.networkController.util.game.GameBase;
import com.networkController.util.screen.ScreenBaseAdapter;
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;

public class MenuScreen extends ScreenBaseAdapter {
    private final AssetManager assetManager;
    String connectedSubnet;
    BitmapFont font;
    /* access modifiers changed from: private */
    public final GameBase game;
    private Texture high_score_button;
    private Texture high_score_button_pressed;
    private Texture options_button;
    private Texture options_button_pressed;
    private Texture panel;
    private Texture play_button;
    private Texture play_button_pressed;
    private Texture quit_button;
    private Texture quit_button_pressed;
    Skin skin;
    private Stage stage;
    boolean testConnection = false;
    private Texture ui_background;
    private Texture ui_foreground;
    private Viewport viewport;

    public MenuScreen(GameBase game2) {
        this.game = game2;
        this.assetManager = game2.getAssetManager();
    }

    public void show() {
        this.viewport = new FitViewport((float) Gdx.graphics.getWidth(), (float) Gdx.graphics.getHeight());
        this.stage = new Stage(this.viewport, this.game.getBatch());
        Table table = new Table();
        this.font = new BitmapFont();
        this.skin = new Skin();
        Pixmap pixmap = new Pixmap(1, 1, Pixmap.Format.RGBA8888);
        pixmap.setColor(Color.WHITE);
        pixmap.fill();
        this.skin.add("white", new Texture(pixmap));
        this.skin.add("default", new BitmapFont());
        this.panel = (Texture) this.assetManager.get(AssetDescriptors.UI_PANEL);
        TextButton.TextButtonStyle textButtonStyle = new TextButton.TextButtonStyle();
        textButtonStyle.up = this.skin.newDrawable("white", Color.DARK_GRAY);
        textButtonStyle.down = this.skin.newDrawable("white", Color.DARK_GRAY);
        textButtonStyle.checked = this.skin.newDrawable("white", Color.BLUE);
        textButtonStyle.over = this.skin.newDrawable("white", Color.LIGHT_GRAY);
        textButtonStyle.font = this.skin.getFont("default");
        textButtonStyle.font.getData().setScale(5.0f);
        this.skin.add("default", textButtonStyle);
        FreeTypeFontGenerator generator = new FreeTypeFontGenerator(Gdx.files.internal("ui/fonts/Minecraft.ttf"));
        FreeTypeFontGenerator.FreeTypeFontParameter parameter = new FreeTypeFontGenerator.FreeTypeFontParameter();
        parameter.size = 100;
        BitmapFont bitmapFont = (BitmapFont) this.assetManager.get(AssetDescriptors.FONT);
        this.font = bitmapFont;
        bitmapFont.getData().setScale(0.5f, 0.5f);
        BitmapFont generateFont = generator.generateFont(parameter);
        this.font = generateFont;
        generateFont.setColor(Color.GREEN);

        this.stage.addActor(table);
        table.defaults().pad(20.0f);
        TextButton startButton = new TextButton("PLAY!", this.skin);
        table.add(startButton).size(350.0f, 100.0f).row();
        final TextButton searchButton = new TextButton("SEARCH", this.skin);
        table.add(searchButton).size(350.0f, 100.0f).row();
        TextButton exitButton = new TextButton("EXIT", this.skin);
        table.add(exitButton).size(350.0f, 100.0f).row();
        startButton.addListener(new ChangeListener() {
            public void changed(ChangeListener.ChangeEvent event, Actor actor) {
                MenuScreen.this.game.setScreen(new NetworkTest(MenuScreen.this.game, MenuScreen.this.connectedSubnet), ScreenTransitions.FADE);
            }
        });
        searchButton.addListener(new ChangeListener() {
            public void changed(ChangeListener.ChangeEvent event, Actor actor) {
                System.out.println("Clicked! Is checked: " + searchButton.isChecked());
                searchButton.setText("Good job!");
                final MenuScreen menuScreen = MenuScreen.this;
                menuScreen.connectedSubnet = menuScreen.searchForConnection();

                /*
                new Thread(new Runnable() {
                    @Override
                    public void run() {
                    }
                }).start();
                */

            }
        });
        exitButton.addListener(new ChangeListener() {
            public void changed(ChangeListener.ChangeEvent event, Actor actor) {
                MenuScreen.this.quit();
            }
        });
        table.center();
        table.setFillParent(true);
        table.pack();
        Gdx.input.setInputProcessor(this.stage);
    }

    public void render(float delta) {
        GdxUtils.clearScreen();
        this.stage.act();
        this.stage.draw();
        //System.out.println(this.connectedSubnet);
        this.game.getBatch().begin();
        this.font.draw((Batch) this.game.getBatch(), (CharSequence) "Connected", ((float) (Gdx.graphics.getWidth() / 2)) - 100.0f, ((float) ((Gdx.graphics.getHeight() / 2) + (Gdx.graphics.getHeight() / 4))) + 50.0f);
        this.game.getBatch().end();
    }

    public void resize(int width, int height) {
        this.viewport.update(width, height, true);
    }

    public void hide() {
        dispose();
    }

    public void dispose() {
        Gdx.input.setInputProcessor((InputProcessor) null);
        this.stage.dispose();
    }

    public InputProcessor getInputProccessor() {
        return this.stage;
    }

    private void play() {
    }

    /* access modifiers changed from: private */
    public void quit() {
        Gdx.app.exit();
    }

    public static String removeNonAlphanumeric(String str) {
        return str.replaceAll("[^a-zA-Z0-9{}:.,\"]", "");
    }

    public String searchForConnection() {
        DatagramSocket testSocket = null;
        int i = 2;
        String subnet = null;

        while (!this.testConnection && (i = i + 1) <= 254) {
        //while (!this.testConnection){
            //for( i++; i <= 254)
            //{}
            //for(int i = 2; i < 254; i++){

            subnet = "192.168.2." + i;
            //subnet = "192.168.2.18";
            Gdx.app.log("AndroidNetwork", "TESTING Connection... " + subnet);
            try {
                testSocket = new DatagramSocket();
                //testSocket.setSoTimeout(1000);
                testSocket.setSoTimeout(200);
                byte[] buffer = new byte[1024];
                testSocket.connect(InetAddress.getByName(subnet), 5500);
                byte[] t = "Client Packet TEST".getBytes();
                testSocket.send(new DatagramPacket(t, t.length));
                DatagramPacket testReceivePacket = new DatagramPacket(buffer, buffer.length);
                testSocket.receive(testReceivePacket);
                String testReceivePacketString = removeNonAlphanumeric(new String(testReceivePacket.getData()));
                if (!testReceivePacketString.equals("")) {
                    Gdx.app.log("AndroidNetwork", "TEST Connected!!!");
                    this.testConnection = true;
                } else {
                    this.testConnection = false;
                }
                Gdx.app.log("AndroidNetwork", testReceivePacket.getSocketAddress().toString());
                Gdx.app.log("AndroidNetwork", testReceivePacketString);
                if (removeNonAlphanumeric(new String(testReceivePacket.getData())).length() > 0) {
                    Gdx.app.log("AndroidNetwork", "TEST GOOD TO GO !!!!");
                } else {
                    Gdx.app.log("AndroidNetwork", "TEST NO GO !!!!");
                }
            } catch (SocketException e) {
                System.out.println("Socket: " + e.getMessage());
                if (testSocket == null) {
                }
            } catch (IOException e2) {
                System.out.println("IO: " + e2.getMessage());
                if (testSocket != null) {
                }
            } catch (Throwable th) {
                if (testSocket != null) {
                    testSocket.close();
                }
                throw th;
            }
            //}

            testSocket.close();
        }
        //subnet = "192.168.2.18";
        return subnet;
    }
}

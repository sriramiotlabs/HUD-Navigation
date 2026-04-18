package com.example.navihud;


import android.Manifest;


import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.SharedPreferences;
import android.content.pm.PackageManager;
import android.graphics.drawable.ColorDrawable;
import android.os.Bundle;
import android.os.Handler;
import android.view.animation.Animation;
import android.view.animation.AnimationUtils;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {
 /*
    public static final String NOTIFICATION_CHANNEL_ID = "10001" ;
    private final static String default_notification_channel_id = "default" ;
    private static final int REQUEST_ENABLE_BT = 1;
    private static final UUID MY_UUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");

    private BluetoothAdapter bluetoothAdapter;
    private BluetoothDevice device;

   // private ConnectedThread connectedThread;
    private ContentResolver contentResolver;
    private PhoneStateListener phoneStateListener;
    private TelephonyManager telephonyManager;
    private BroadcastReceiver callReceiver;
    private boolean isConnected = false;
    private static final int PERMISSION_REQUEST_CODE = 1;
    private ListView deviceListView;
    private List<BluetoothDevice> deviceList;
    private ArrayAdapter<String> deviceListAdapter;
    private BluetoothSocket bluetoothSocket;
    private OutputStream outputStream;
    private static final int REQUEST_PERMISSION_BT = 2;
    @RequiresApi(api = Build.VERSION_CODES.JELLY_BEAN_MR2)*/
    private TextView textview;
    @Override
    protected void onCreate (Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        textview = findViewById(R.id.textview);
        getSupportActionBar().setBackgroundDrawable(new ColorDrawable(getResources().getColor(R.color.white)));
        Animation animation1 =
                AnimationUtils.loadAnimation(getApplicationContext(),
                        R.anim.fade);
        textview.startAnimation(animation1);
      //  txtView = findViewById(R.id.textView);

       // bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();


        new Handler().postDelayed(new Runnable() {
            @Override
            public void run() {
                Intent intent = new Intent(MainActivity.this, MainActivity2.class);
                startActivity(intent);
                finish();
            }
        }, 2700);






    }










}


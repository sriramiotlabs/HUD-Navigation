package com.example.navihud;

import android.annotation.SuppressLint;
import android.content.Context ;
import android.content.SharedPreferences;
import android.database.Cursor;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.provider.ContactsContract;
import android.service.notification.NotificationListenerService ;
import android.service.notification.StatusBarNotification ;
import android.telephony.PhoneStateListener;
import android.telephony.TelephonyManager;
import android.util.Log ;

import androidx.annotation.RequiresApi;

@SuppressLint("OverrideAbstract")
@RequiresApi(api = Build.VERSION_CODES.JELLY_BEAN_MR2)
public class NotificationListener extends NotificationListenerService {
    private String TAG = this .getClass().getSimpleName() ;
    Context context ;
    static MyListener myListener ;
    String pac_name;
    String textData;
    String ticker;
    String data;
    String comdata;
    TelephonyManager telephonyManager;
    PhoneStateListener phoneStateListener;
    @Override
    public void onCreate () {
        super .onCreate() ;
        context = getApplicationContext() ;

    }
    @RequiresApi(api = Build.VERSION_CODES.KITKAT)
    @Override
    public void onNotificationPosted (StatusBarNotification sbn) {
        Log.i(TAG, "********** onNotificationPosted");
        SharedPreferences sharedPreferences = PreferenceManager.getDefaultSharedPreferences(this);
        String packageName = sbn.getPackageName();
        if ((packageName.equals("com.google.android.apps.maps")||packageName.equals("com.mmi.maps"))&& sharedPreferences.getBoolean("maps_enabled", false)) {

        Bundle extras = sbn.getNotification().extras;
        if (extras.getCharSequence("android.text") != null) {
            textData = extras.getCharSequence("android.text").toString();
        } else {
            textData = "";
        }
        if (extras.getString("android.title") != null) {
            data = extras.getString("android.title");
        } else {
            data = "";
        }
        if (sbn.getNotification().tickerText != null) {
            ticker = sbn.getNotification().tickerText.toString();
        }
        pac_name = sbn.getPackageName();
        // data=ticker;

        //if (pac_name == "com.mmi.maps" || pac_name == "com.google.android.apps.maps"){
        comdata = pac_name + data + textData + ticker;
        Log.i(TAG, "ID :" + sbn.getId() + " \t " + sbn.getNotification().tickerText + " \t " + sbn.getPackageName());
        myListener.setValue(pac_name, data, textData, ticker);


        }
       if (packageName.equals("com.google.android.dialer") && sharedPreferences.getBoolean("call_enabled", false)) {
            Bundle extras = sbn.getNotification().extras;
            if (extras.getCharSequence("android.text") != null) {
                textData = extras.getCharSequence("android.text").toString();
            } else {
                textData = "";
            }
            if (extras.getString("android.title") != null) {
                data = extras.getString("android.title");
            } else {
                data = "";
            }
            if (sbn.getNotification().tickerText != null) {
                ticker = sbn.getNotification().tickerText.toString();
            }
            pac_name = sbn.getPackageName();
            // data=ticker;

            //if (pac_name == "com.mmi.maps" || pac_name == "com.google.android.apps.maps"){
            comdata = pac_name + data + textData + ticker;
            Log.i(TAG, "ID :" + sbn.getId() + " \t " + sbn.getNotification().tickerText + " \t " + sbn.getPackageName());
            myListener.setValue(pac_name, data, textData, ticker);
        }
    }
  /*  @Override
    public void onNotificationRemoved (StatusBarNotification sbn) {
        Log. i ( TAG , "********** onNotificationRemoved" ) ;
        Log. i ( TAG , "ID :" + sbn.getId() + " \t " + sbn.getNotification(). tickerText + " \t " + sbn.getPackageName()) ;
        myListener .setValue( "Remove: " + sbn.getPackageName()) ;
    }*/
        public void setListener (MyListener myListener){
            NotificationListener.myListener = myListener;
        }

}

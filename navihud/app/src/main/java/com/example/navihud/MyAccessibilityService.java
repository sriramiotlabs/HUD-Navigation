package com.example.navihud;

import android.accessibilityservice.AccessibilityService;
import android.app.Service;
import android.content.Intent;
import android.os.IBinder;
import android.view.accessibility.AccessibilityEvent;

import androidx.annotation.Nullable;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class MyAccessibilityService extends AccessibilityService {
    String directions = "";
    String distanceString="";
    static dir_list di_list;
    @Override
    public void onAccessibilityEvent(AccessibilityEvent event) {
        if (event.getEventType() == AccessibilityEvent.TYPE_VIEW_TEXT_CHANGED) {
            if ("com.mmi.maps".equals(event.getPackageName())) {
                CharSequence text = (CharSequence) event.getText();
                if (text != null && text.length() > 0) {
                    String textString = text.toString();

                    double distance = -1; // Use a double to handle meters and kilometers

                    // Match for directions (e.g., "turn left" or "turn right")
                    Pattern directionsPattern = Pattern.compile("(?i)(left|right|straight)");
                    Matcher directionsMatcher = directionsPattern.matcher(textString);

                    while (directionsMatcher.find()) {
                        directions = directionsMatcher.group();
                    }

                    // Match for distances (e.g., "40m" or "2.5km")
                    Pattern distancePattern = Pattern.compile("\\b(\\d+(?:\\.\\d+)?)([mk]?m)\\b");
                    Matcher distanceMatcher = distancePattern.matcher(textString);

                    if (distanceMatcher.find()) {
                        String distanceValueStr = distanceMatcher.group(1);
                        String unit = distanceMatcher.group(2);

                        if ("m".equalsIgnoreCase(unit)) {
                            // Convert meters to kilometers (1 km = 1000 meters)
                            distance = Double.parseDouble(distanceValueStr) / 1000.0;
                        } else if ("km".equalsIgnoreCase(unit)) {
                            // Kilometers are directly parsed
                            distance = Double.parseDouble(distanceValueStr);
                        }
                    }
                    distanceString = Double.toString(distance);
                    // Do something with directions and distance
                    if (!directions.isEmpty()) {
                        // System.out.println("Directions: " + directions);
                        // connectedThread.write(directions);

                    }
                    if (distance >= 0) {
                        //System.out.println("Distance: " + distance + (distance < 1 ? " km" : " meters"));
                        //connectedThread.write("Distance: " + distanceString + (distance < 1 ? "km" : "m"));
                    }
                }
                di_list.dir_Value(directions,distanceString);
            }
        }
    }
    @Override
    public void onInterrupt() {
        // Handle accessibility service interruption
    }

    @Override
    protected void onServiceConnected() {
        super.onServiceConnected();
        // Initialization code if needed

    }
    public static void setDirListener(dir_list di_list) {
        MyAccessibilityService.di_list = di_list ;
    }
}

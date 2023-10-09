package com.defold.hgpoint;

import android.util.Log;
import android.app.Activity;
import android.app.Application;


import android.telephony.TelephonyManager;
import android.text.TextUtils;

public class CountryGetterJNI {
    private static final String TAG = "CountryGetter";

    private Activity activity;
    private Application application;

    public CountryGetterJNI(Activity activity) {
        this.activity = activity;
        this.application = activity.getApplication();
    }

    public String GetCountry() {
        TelephonyManager telephonyManager = (TelephonyManager)activity.getSystemService(activity.getApplicationContext().TELEPHONY_SERVICE);
        String iso=telephonyManager.getNetworkCountryIso();

        if(TextUtils.isEmpty(iso))
            iso=telephonyManager.getSimCountryIso();
        if(TextUtils.isEmpty(iso))
            iso=activity.getResources().getConfiguration().getLocales().get(0).getCountry();

        if (iso != null)
            return iso.toUpperCase();
        return "";
    }
}

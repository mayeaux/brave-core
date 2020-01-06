/**
 * Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

package org.chromium.chrome.browser.util;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.os.RemoteException;
import com.android.installreferrer.api.InstallReferrerClient;
import com.android.installreferrer.api.InstallReferrerClient.InstallReferrerResponse;
import com.android.installreferrer.api.InstallReferrerStateListener;
import com.android.installreferrer.api.ReferrerDetails;
import org.chromium.base.Log;

public class BraveReferrer extends BroadcastReceiver implements InstallReferrerStateListener {
    private static final String TAG = "BraveReferrer";

    private InstallReferrerClient referrerClient;

    @Override
    public void onReceive(Context context, Intent intent) {
        if(intent.getAction() != null) {
            if(intent.getAction().equals(Intent.ACTION_PACKAGE_FIRST_LAUNCH)) {
                referrerClient = InstallReferrerClient.newBuilder(context).build();
                referrerClient.startConnection(this);
            }
        }
    }

    @Override
    public void onInstallReferrerSetupFinished(int responseCode) {
        switch (responseCode) {
            case InstallReferrerResponse.OK:
                try {
                    ReferrerDetails response = referrerClient.getInstallReferrer();
                    String referrer = response.getInstallReferrer();
                    long clickTimestamp = response.getReferrerClickTimestampSeconds();
                    long installTimestamp = response.getInstallBeginTimestampSeconds();
                    Log.w(TAG, "InstallReferrer " + referrer);
                    // TODO(samartnik): save referrer to promo_code file
                    referrerClient.endConnection();
                } catch (RemoteException e) {
                    Log.e(TAG, e.getMessage());
                }
                break;
            case InstallReferrerResponse.FEATURE_NOT_SUPPORTED:
                Log.e(TAG, "API not available on the current Play Store app");
                break;
            case InstallReferrerResponse.SERVICE_UNAVAILABLE:
                Log.e(TAG, "Connection couldn't be established");
                break;
        }
    }

    @Override
    public void onInstallReferrerServiceDisconnected() {
        Log.e(TAG, "Install referrer service was disconnected");
    }
}

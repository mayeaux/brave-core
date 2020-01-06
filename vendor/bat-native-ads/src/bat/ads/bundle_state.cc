/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "bat/ads/bundle_state.h"

#include "bat/ads/internal/json_helper.h"
#include "bat/ads/internal/uri_helper.h"

namespace ads {

BundleState::BundleState() :
    catalog_id(""),
    catalog_version(0),
    catalog_ping(0),
    catalog_last_updated_timestamp_in_seconds(0),
    categories({}) {}

BundleState::BundleState(const BundleState& state):
    catalog_id(state.catalog_id),
    catalog_version(state.catalog_version),
    catalog_ping(state.catalog_ping),
    catalog_last_updated_timestamp_in_seconds(
        state.catalog_last_updated_timestamp_in_seconds),
    categories(state.categories) {}

BundleState::~BundleState() = default;

const std::string BundleState::ToJson() const {
  std::string json;
  SaveToJson(*this, &json);
  return json;
}

Result BundleState::FromJson(
    const std::string& json,
    const std::string& json_schema,
    std::string* error_description) {
  rapidjson::Document bundle;
  bundle.Parse(json.c_str());

  auto result = helper::JSON::Validate(&bundle, json_schema);
  if (result != SUCCESS) {
    if (error_description != nullptr) {
      *error_description = helper::JSON::GetLastError(&bundle);
    }

    return result;
  }

  std::map<std::string, std::vector<CreativeAdNotificationInfo>> new_categories;

  if (bundle.HasMember("categories")) {
    for (const auto& category : bundle["categories"].GetObject()) {
      for (const auto& creative_ad_notification : category.value.GetArray()) {
        CreativeAdNotificationInfo info;

        if (creative_ad_notification.HasMember("creativeSetId")) {
          info.creative_set_id =
              creative_ad_notification["creativeSetId"].GetString();
        }

        if (creative_ad_notification.HasMember("campaignId")) {
          info.campaign_id = creative_ad_notification["campaignId"].GetString();
        }

        if (creative_ad_notification.HasMember("startTimestamp")) {
          info.start_timestamp =
              creative_ad_notification["startTimestamp"].GetString();
        }

        if (creative_ad_notification.HasMember("endTimestamp")) {
          info.end_timestamp =
              creative_ad_notification["endTimestamp"].GetString();
        }

        if (creative_ad_notification.HasMember("dailyCap")) {
          info.daily_cap = creative_ad_notification["dailyCap"].GetUint();
        }

        if (creative_ad_notification.HasMember("perDay")) {
          info.per_day = creative_ad_notification["perDay"].GetUint();
        }

        if (creative_ad_notification.HasMember("totalMax")) {
          info.total_max = creative_ad_notification["totalMax"].GetUint();
        }

        std::vector<std::string> regions;
        if (creative_ad_notification.HasMember("regions")) {
          for (const auto& region :
              creative_ad_notification["regions"].GetArray()) {
            regions.push_back(region.GetString());
          }
        }
        info.regions = regions;

        info.advertiser = creative_ad_notification["advertiser"].GetString();
        info.notification_text =
            creative_ad_notification["notificationText"].GetString();
        info.notification_url = helper::Uri::GetUri(
            creative_ad_notification["notificationURL"].GetString());
        info.uuid = creative_ad_notification["uuid"].GetString();

        if (new_categories.find(category.name.GetString()) ==
            new_categories.end()) {
          new_categories.insert({category.name.GetString(), {}});
        }

        new_categories.at(category.name.GetString()).push_back(info);
      }
    }
  }

  categories = new_categories;

  return SUCCESS;
}

void SaveToJson(JsonWriter* writer, const BundleState& state) {
  writer->StartObject();

  writer->String("categories");
  writer->StartObject();

  for (const auto& category : state.categories) {
    writer->String(category.first.c_str());
    writer->StartArray();

    for (const auto& ad : category.second) {
      writer->StartObject();

      writer->String("creativeSetId");
      writer->String(ad.creative_set_id.c_str());

      writer->String("campaignId");
      writer->String(ad.campaign_id.c_str());

      writer->String("startTimestamp");
      writer->String(ad.start_timestamp.c_str());

      writer->String("endTimestamp");
      writer->String(ad.end_timestamp.c_str());

      writer->String("dailyCap");
      writer->Uint(ad.daily_cap);

      writer->String("perDay");
      writer->Uint(ad.per_day);

      writer->String("totalMax");
      writer->Uint(ad.total_max);

      writer->String("regions");
      writer->StartArray();
      for (const auto& region : ad.regions) {
        writer->String(region.c_str());
      }
      writer->EndArray();

      writer->String("advertiser");
      writer->String(ad.advertiser.c_str());

      writer->String("notificationText");
      writer->String(ad.notification_text.c_str());

      writer->String("notificationURL");
      writer->String(ad.notification_url.c_str());

      writer->String("uuid");
      writer->String(ad.uuid.c_str());

      writer->EndObject();
    }

    writer->EndArray();
  }

  writer->EndObject();

  writer->EndObject();
}

}  // namespace ads

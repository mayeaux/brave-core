/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

import { action } from 'typesafe-actions'

// Types
import { InitialData } from '../api/initialData'
import { types } from '../constants/top_sites_types'

export const setInitialTopSitesData = (initialData: InitialData) => {
  return action(types.TOP_SITES_SET_INITIAL_DATA, initialData)
}

export const topSitesDataUpdated = (gridSites: NewTab.Site[]) => {
  return action(types.TOP_SITES_DATA_UPDATED, { gridSites })
}

export const toggleTopSitePinned = (pinnedSite: NewTab.Site) => {
  return action(types.TOP_SITES_TOGGLE_SITE_PINNED, { pinnedSite })
}

export const removeTopSite = (ignoredSite: NewTab.Site) => {
  return action(types.TOP_SITES_REMOVE_SITE, { ignoredSite })
}

export const undoRemoveTopSite = () => {
  return action(types.TOP_SITES_UNDO_REMOVE_SITE)
}

export const undoRemoveAllTopSites = () => {
  return action(types.TOP_SITES_UNDO_REMOVE_ALL_SITES)
}

export const showSiteRemovalNotification = (shouldShow: boolean) => {
  return action(types.TOP_SITES_SHOW_SITE_REMOVAL_NOTIFICATION, { shouldShow })
}

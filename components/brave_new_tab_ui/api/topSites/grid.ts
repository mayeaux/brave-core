/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

import { getGridSites } from '../../state/gridState'

/**
 * Obtains a list of top sites from Chromium back-end
 * @returns {Promise<NewTab.Site[]>}
 */
export function getTopSites (): Promise<NewTab.Site[]> {
  return new Promise(resolve => {
    chrome.topSites.get((topSites: NewTab.Site[]) => {
      const formattedTopSites = getGridSites(topSites)
      resolve(formattedTopSites || [])
    })
  })
}

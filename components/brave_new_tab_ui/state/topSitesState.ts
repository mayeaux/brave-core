/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

import { isTopSitePinned } from '../helpers/newTabUtils'

export function topSitesReducerSetInitialData (
  state: NewTab.State,
  topSites: NewTab.Site[]
): NewTab.State {
  const emptyGridSites: boolean = state.gridSites.length === 0
  const noGridSitesProperty: boolean = 'gridSites' in state === false

  if (emptyGridSites || noGridSitesProperty) {
    state = topSitesReducerDataUpdated(state, topSites)
  }

  state = { ...state, topSites }
  return state
}

export function topSitesReducerDataUpdated (
  state: NewTab.State,
  sitesData: NewTab.Site[]
): NewTab.State {
  let updatedGridSites: NewTab.Site[] = []
  // iterate over all items and populate a new array with them.
  // if an item is pinned, add it to its original index inside
  // the new array without removing anything. this will push other
  // items to the right, which is what we want
  for (const site of sitesData) {
    if (site.pinnedIndex === undefined) {
      updatedGridSites.push(site)
    } else {
      updatedGridSites.splice(site.pinnedIndex, 0, site)
    }
  }

  state = { ...state, gridSites: updatedGridSites }
  return state
}

export function topSitesReducerToggleTopSitePinned (
  state: NewTab.State,
  pinnedSite: NewTab.Site
): NewTab.State {
  const updatedGridSites = state.gridSites
    .map((site: NewTab.Site, index: number) => {
      if (site.url === pinnedSite.url) {
        return {
          ...site,
          pinnedIndex: isTopSitePinned(site) ? undefined : index
        }
      }
      return site
    })
  state = topSitesReducerDataUpdated(state, updatedGridSites)
  return state
}

export function topSitesReducerRemoveSite (
  state: NewTab.State,
  ignoredSite: NewTab.Site
): NewTab.State {
  state = {
    ...state,
    ignoredTopSites: [ ...state.ignoredTopSites, ignoredSite ]
  }
  const filterExcludedFromGridSites = state.gridSites
    .filter((site: NewTab.Site) => {
      // in the updatedGridSites we only want sites not excluded by the user
      return state.ignoredTopSites
        .every((excludedSite: NewTab.Site) => excludedSite.url !== site.url)
    })
  state = topSitesReducerDataUpdated(state, filterExcludedFromGridSites)
  return state
}

export function topSitesReducerUndoRemoveSite (
  state: NewTab.State
): NewTab.State {
  if (state.ignoredTopSites.length === 0) {
    // nothing to see here, move along.
    return state
  }
  // remove the last item from the array
  const removedItem: any = [state.ignoredTopSites.pop()]
  // push back the item into the grid array by adding the site
  state = topSitesReducerAddSites(state, removedItem)
  return state
}

export function topSitesReducerUndoRemoveAllSites (
  state: NewTab.State
): NewTab.State {
  // erase all ignored sites data
  const allRemovedSites: NewTab.Site[] = state.ignoredTopSites
  // remove all sites from the exclusion list
  state = { ...state, ignoredTopSites: [] }
  // add them all back into grid
  state = topSitesReducerAddSites(state, allRemovedSites)
  return state
}

export function topSitesReducerAddSites (
  state: NewTab.State,
  addedSites: NewTab.Site[]
): NewTab.State {
  if (addedSites.length === 0) {
    return state
  }
  const currentGridSitesWithNewItems: NewTab.Site[] = [
    ...addedSites,
    ...state.gridSites
  ]
  state = topSitesReducerDataUpdated(state, currentGridSitesWithNewItems)
  return state
}

export function topSitesReducerShowSiteRemovalNotification (
  state: NewTab.State,
  shouldShow: boolean
): NewTab.State {
  state = { ...state, shouldShowSiteRemovalNotification: shouldShow }
  return state
}

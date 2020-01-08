/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

import * as React from 'react'
import {
  Page,
  Header,
  ClockWidget as Clock,
  Footer,
  App,
  PosterBackground,
  Gradient,
  RewardsWidget as Rewards
} from '../../components/default'

// Helpers
import arrayMove from 'array-move'
import { isTopSitePinned } from '../../helpers/newTabUtils'
import { gridSitesSize } from '../../constants/new_tab_interface'

// Types
import { SortEnd } from 'react-sortable-hoc'

// Components
import Stats from './stats'
import TopSitesGrid from './topSitesGrid'
import FooterInfo from './footerInfo'
import SiteRemovalNotification from './notification'

interface Props {
  newTabData: NewTab.State
  topSitesData: NewTab.TopSitesState
  actions: any
  saveShowBackgroundImage: (value: boolean) => void
  saveShowClock: (value: boolean) => void
  saveShowTopSites: (value: boolean) => void
  saveShowStats: (value: boolean) => void
  saveShowRewards: (value: boolean) => void
}

interface State {
  onlyAnonWallet: boolean
  showSettingsMenu: boolean
  backgroundHasLoaded: boolean
}

class NewTabPage extends React.Component<Props, State> {
  state = {
    onlyAnonWallet: false,
    showSettingsMenu: false,
    backgroundHasLoaded: false
  }

  componentDidMount () {
    // if a notification is open at component mounting time, close it
    this.props.actions.showSiteRemovalNotification(false)
    this.trackCachedImage()
  }

  componentDidUpdate (prevProps: Props) {
    if (!prevProps.newTabData.showBackgroundImage &&
          this.props.newTabData.showBackgroundImage) {
      this.trackCachedImage()
    }
    if (prevProps.newTabData.showBackgroundImage &&
      !this.props.newTabData.showBackgroundImage) {
      // reset loaded state
      this.setState({ backgroundHasLoaded: false })
    }
  }

  trackCachedImage () {
    if (this.props.newTabData.showBackgroundImage &&
        this.props.newTabData.backgroundImage &&
        this.props.newTabData.backgroundImage.source) {
      const imgCache = new Image()
      imgCache.src = this.props.newTabData.backgroundImage.source
      console.timeStamp('image start loading...')
      imgCache.onload = () => {
        console.timeStamp('image loaded')
        this.setState({
          backgroundHasLoaded: true
        })
      }
    }
  }

  onSortEnd = ({ oldIndex, newIndex }: SortEnd) => {
    const { newTabData } = this.props
    // do not update topsites order if the drag
    // destination is a pinned tile
    const gridSite = newTabData.gridSites[newIndex]
    if (!gridSite || isTopSitePinned(gridSite)) {
      return
    }
    const items = arrayMove(newTabData.gridSites, oldIndex, newIndex)
    this.props.actions.topSitesDataUpdated(items)
  }
  toggleShowBackgroundImage = () => {
    this.props.saveShowBackgroundImage(
      !this.props.newTabData.showBackgroundImage
    )
  }

  toggleShowClock = () => {
    this.props.saveShowClock(
      !this.props.newTabData.showClock
    )
  }

  toggleShowStats = () => {
    this.props.saveShowStats(
      !this.props.newTabData.showStats
    )
  }

  toggleShowTopSites = () => {
    this.props.saveShowTopSites(
      !this.props.newTabData.showTopSites
    )
  }

  toggleShowRewards = () => {
    this.props.saveShowRewards(
      !this.props.newTabData.showRewards
    )
  }

  enableAds = () => {
    chrome.braveRewards.saveAdsSetting('adsEnabled', 'true')
  }

  enableRewards = () => {
    this.props.actions.onRewardsSettingSave('enabledMain', '1')
  }

  createWallet = () => {
    this.props.actions.createWallet()
  }

  dismissNotification = (id: string) => {
    this.props.actions.dismissNotification(id)
  }

  closeSettings = () => {
    this.setState({ showSettingsMenu: false })
  }

  toggleSettings = () => {
    this.setState({ showSettingsMenu: !this.state.showSettingsMenu })
  }

  render () {
    const { newTabData, topSitesData, actions } = this.props
    const { showSettingsMenu } = this.state
    const { rewardsState } = newTabData

    if (!newTabData) {
      return null
    }

    return (
      <App dataIsReady={newTabData.initialDataLoaded}>
        <PosterBackground
          hasImage={newTabData.showBackgroundImage}
          imageHasLoaded={this.state.backgroundHasLoaded}
        >
          {newTabData.showBackgroundImage && newTabData.backgroundImage &&
            <img src={newTabData.backgroundImage.source} />
          }
        </PosterBackground>
        {newTabData.showBackgroundImage &&
          <Gradient
            imageHasLoaded={this.state.backgroundHasLoaded}
          />
        }
        <Page>
          <Header>
            <Stats
              textDirection={newTabData.textDirection}
              stats={newTabData.stats}
              showWidget={newTabData.showStats}
              hideWidget={this.toggleShowStats}
              menuPosition={'right'}
            />
            <Clock
              textDirection={newTabData.textDirection}
              showWidget={newTabData.showClock}
              hideWidget={this.toggleShowClock}
              menuPosition={'left'}
            />
            <Rewards
              {...rewardsState}
              onCreateWallet={this.createWallet}
              onEnableAds={this.enableAds}
              onEnableRewards={this.enableRewards}
              textDirection={newTabData.textDirection}
              showWidget={newTabData.showRewards}
              hideWidget={this.toggleShowRewards}
              onDismissNotification={this.dismissNotification}
              menuPosition={'left'}
            />
            {
              topSitesData.gridSites.length
                ? (
                  <TopSitesGrid
                    actions={actions}
                    gridSites={topSitesData.gridSites}
                    // react-sortable-hoc props
                    onSortEnd={this.onSortEnd}
                    axis='xy'
                    lockToContainerEdges={true}
                    lockOffset={'15%'}
                    // child widget element props
                    textDirection={newTabData.textDirection}
                    showWidget={newTabData.showTopSites}
                    menuPosition={'right'}
                    hideWidget={this.toggleShowTopSites}
                    // styled-component element props
                    blockNumber={gridSitesSize}
                  />
                ) : null
            }
            {
              topSitesData.shouldShowSiteRemovalNotification
              ? (
                <SiteRemovalNotification actions={actions} />
              ) : null
            }
          </Header>
          <Footer>
            <FooterInfo
              textDirection={newTabData.textDirection}
              onClickOutside={this.closeSettings}
              backgroundImageInfo={newTabData.backgroundImage}
              onClickSettings={this.toggleSettings}
              showSettingsMenu={showSettingsMenu}
              showPhotoInfo={newTabData.showBackgroundImage}
              toggleShowBackgroundImage={this.toggleShowBackgroundImage}
              toggleShowClock={this.toggleShowClock}
              toggleShowStats={this.toggleShowStats}
              toggleShowTopSites={this.toggleShowTopSites}
              showBackgroundImage={newTabData.showBackgroundImage}
              showClock={newTabData.showClock}
              showStats={newTabData.showStats}
              showTopSites={newTabData.showTopSites}
              showRewards={newTabData.showRewards}
              toggleShowRewards={this.toggleShowRewards}
            />
          </Footer>
        </Page>
      </App>
    )
  }
}

export default NewTabPage

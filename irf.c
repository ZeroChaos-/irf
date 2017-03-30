/*
 * Initiate Radiation First
 */
#include <linux/module.h>
#include <linux/kernel.h>
#include <net/mac80211.h>
#define DRIVER_AUTHOR "Zero_Chaos <sidhayn@gmail.com>"
#define DRIVER_DESC "transmit uninhibitor"
MODULE_LICENSE("Dual BSD/GPL");

static void force_clear_tx_inhibit(struct wiphy *wiphy)
{
  struct ieee80211_supported_band *sband;
  struct ieee80211_channel *ch;
  unsigned int i;

  if(wiphy->bands[NL80211_BAND_2GHZ])
    sband = wiphy->bands[NL80211_BAND_2GHZ];
    for (i = 0; i < sband->n_channels; i++) {
      ch = &sband->channels[i];

      if (ch->flags & IEEE80211_CHAN_NO_IR)
        ch->flags &= ~IEEE80211_CHAN_NO_IR;
      if (ch->flags & IEEE80211_CHAN_RADAR)
        ch->flags &= ~IEEE80211_CHAN_RADAR;
    }

  if(wiphy->bands[NL80211_BAND_5GHZ])
    sband = wiphy->bands[NL80211_BAND_5GHZ];
    for (i = 0; i < sband->n_channels; i++) {
      ch = &sband->channels[i];

      if (ch->flags & IEEE80211_CHAN_NO_IR)
        ch->flags &= ~IEEE80211_CHAN_NO_IR;
      if (ch->flags & IEEE80211_CHAN_RADAR)
        ch->flags &= ~IEEE80211_CHAN_RADAR;
    }
}

int init_module(void)
{
  printk(KERN_INFO "IRF loaded\n");
  //somehow we need to do a lookup for all the registered wiphys the pass them
  //one at a time to this function which should magically unlock the channels
  //force_clear_tx_inhibit(wiphy);
  return 0;
}


void cleanup_module(void)
{
  printk(KERN_INFO "IRF unloaded\n");
}

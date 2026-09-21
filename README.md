# eak_ctl

MQTT LD_PRELOAD shim for Tantos Neo HD SE Tuya.

Home Assistant MQTT entities:

  - Switch `Автоматическое открывание` - sets auto open once on Panel 1.
  - Switch `Не беспокоить` - sets do not disturb.
  - Button `Сбросить вызов` - calls `Act_ExecuteTakeoff` - end the call and exit call screen.
  - Number `Смещение байта в конфиге` - read byte from `vConfigData` global object.
  - Number `Значение байта в конфиге` - write byte to `vConfigData` global object.

# Modified application

`eakui.EApp.V10944.patched` - modified binary file V10944 with bug fixes.
`eakui.EApp.V10945.patched` - modified binary file V10945 with bug fixes.

Bug fixes:

 - Send Tuya DP based on panel ID (was hardcoded to 0).

# tuya-local device config file

Since `tuya-local` maintainer [refused](https://github.com/make-all/tuya-local/issues/5757) adding device support to the repository, I put the `tantos_neohdsetuya_videodoorbell.yaml` file here.

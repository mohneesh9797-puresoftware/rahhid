include $(TOPDIR)/rules.mk

PKG_NAME:=rahhid
#PKG_VERSION:=0.0.1
PKG_RELEASE:=1
PKG_REV:=11812e3f1e0c81b9ab0f9cf8b03177d3b172c4a6
PKG_VERSION:=$(PKG_REV)

PKG_SOURCE:=rahhid-$(PKG_VERSION).tar.bz2
PKG_SOURCE_SUBDIR:=rahhid-$(PKG_VERSION)
PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=git://github.com/burghardt/rahhid.git
PKG_SOURCE_VERSION:=$(PKG_REV)

PKG_BUILD_DIR:=$(BUILD_DIR)/rahhid-$(PKG_VERSION)
PKG_BUILD_DEPENDS:=hidapi

include $(INCLUDE_DIR)/package.mk

define Package/rahhid
  SECTION:=base
  CATEGORY:=Network
  TITLE:=Radioactive@Home HID driver based on libhidapi (with simple ThingSpeak support)
  URL:=https://github.com/burghardt/rahhid/
  DEPENDS:=+hidapi
endef

define Package/rahhid/description
 Radioactive@Home Geiger–Müller counters USB HID communication utility.
 Read sensors state and upload data to ThingSpeak server.
endef

define Build/Configure
endef

define Package/rahhid/install
		$(INSTALL_DIR) $(1)/usr/bin
		$(INSTALL_BIN) $(PKG_BUILD_DIR)/rahhid $(1)/usr/bin/
endef

$(eval $(call BuildPackage,rahhid,+libhidapi-libusb))

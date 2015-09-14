/*
 * Android File Transfer for Linux: MTP client for android devices
 * Copyright (C) 2015  Vladimir Menshakov

 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */
#ifndef USB_DEVICE_H
#define USB_DEVICE_H

#include <mtp/types.h>
#include <usb/Device.h>
#include <usb/Interface.h>

#include <usb/usb.h>

#include <vector>

namespace mtp { namespace usb
{
	class Configuration : Noncopyable
	{
		IOUSBDeviceInterface			**_dev;
		IOUSBConfigurationDescriptorPtr	_conf;

		std::vector<IOUSBInterfaceInterface **> _interfaces;

	public:
		Configuration(IOUSBDeviceInterface ** dev, IOUSBConfigurationDescriptorPtr conf);
		~Configuration() { }

		int GetIndex() const
		{ return _conf->bConfigurationValue; }

		int GetInterfaceCount() const
		{ return _interfaces.size(); }

		int GetInterfaceAltSettingsCount(int idx) const
		{ return 1; }

		InterfacePtr GetInterface(DevicePtr device, ConfigurationPtr config, int idx, int settings) const
		{ return std::make_shared<Interface>(device, config, _interfaces.at(idx)); }
	};

	class DeviceDescriptor
	{
	private:
		IOUSBDeviceInterface			**_dev;

	public:
		DeviceDescriptor(io_service_t desc);
		~DeviceDescriptor();

		u16 GetVendorId() const;
		u16 GetProductId() const;

		DevicePtr Open(ContextPtr context);
		DevicePtr TryOpen(ContextPtr context);

		int GetConfigurationsCount() const;

		ConfigurationPtr GetConfiguration(int conf);
		ByteArray GetDescriptor();
	};
	DECLARE_PTR(DeviceDescriptor);

}}

#endif


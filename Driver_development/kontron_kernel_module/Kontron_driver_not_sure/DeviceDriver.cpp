
#include "DeviceDriver.h"
//#include "KontronDeviceException.h"

static constexpr std::uint8_t INITIALIZING_DATA = 0;
static constexpr std::uint32_t BYTE_LENGTH = 8;

DeviceDriver::DeviceDriver() :
	m_device()
{
	getFirmwareVersion();
}

uint32_t DeviceDriver::getFirmwareVersion()
{
	m_device.writeCommand(Device::CMD_INFO);
	uint32_t info1_a = m_device.readData();
	uint32_t info1_b = m_device.readData();
	uint32_t info1_c = m_device.readData();

	m_device.writeCommand(Device::CMD_INFO2);
	uint32_t info2 = m_device.readData();
	return ((info1_a << (3 * BYTE_LENGTH)) | (info1_b << (2 * BYTE_LENGTH)) | (info1_c << BYTE_LENGTH) | info2);
}

bool DeviceDriver::canSetGpioDirection(DeviceDriver::GpioChannelIndex channel, DeviceDriver::GpioDirection direction) const
{
	if ((channel >= 0) && (channel < Device::NUM_GPIO))
	{
		if (direction == DeviceDriver::GpioDirection::INPUT)
		{
			return true;
		}
		// else if (direction == DeviceDriver::GpioDirection::OUTPUT)
		// {
		// 	throw exception
		// }
	}
	return false;
}

void DeviceDriver::canSetGpioDirection(DeviceDriver::GpioChannelIndex channel, DeviceDriver::GpioDirection direction)
{
	if (! DeviceDriver::canSetGpioDirection(channel, direction))
	{
		//throw exception
	}

	if (direction == DeviceDriver::GpioDirection::INPUT)
	{
		m_device.writeCommand(Device::CMD_GPIO_SETDIR);
		m_device.writeData(channel);
		m_device.writeData(Device::GPIO_SETDIR_INPUT | Device::GPIO_SETDIR_PULLUP);
	} 
	else if (direction == DeviceDriver::GpioDirection::OUTPUT)
	{
		//throw exception
	}

}

DeviceDriver::GpioInputValue DeviceDriver::getGpioInput(DeviceDriver::GpioChannelIndex channel)
{
	m_device.writeCommand(Device::CMD_GPIO_GET);
	m_device.writeData(channel);
	return m_device.readData();
}

double DeviceDriver::getTemperature(TemperatureChannelIndex channel)
{
	constexpr double temperature_conversion = 1.0 /64;

	m_device.writeCommand(static_cast<Device::Command>(Device::CMD_GET_CPUTEMP +2 * channel));
	m_device.writeData(INITIALIZING_DATA);
	std::uint32_t low_byte = m_device.readData();
	std::uint32_t high_byte = m_device.readData();
	
	return (((high_byte << BYTE_LENGTH) | low_byte) * temperature_conversion);
}

uint32_t DeviceDriver::getFanSpeed(FanChannelIndex channel)
{
	m_device.writeCommand(Device::CMD_GET_FANRPM);
	m_device.writeData(channel);
	std::uint32_t low_byte = m_device.readData();
	std::uint32_t high_byte= m_device.readData();

	return ((high_byte << BYTE_LENGTH) | low_byte);
}
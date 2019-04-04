
#include "Device.h"

class DeviceDriver
{
	public:
		using GpioChannelIndex = std::uint32_t;
		using GpioInputValue = std::uint32_t;
		using GpioOutputValue = std::uint32_t;
		using TemperatureChannelIndex = std::int32_t;
		using FanChannelIndex = std::int32_t;

		enum class GpioDirection
		{
			INPUT,
			OUTPUT
		};
	 /// \brief Class constructor, initializes device driver
    DeviceDriver();

    /// \brief Default destructor
    virtual ~DeviceDriver() = default;

    /// \brief Gets firmware version from the device
    std::uint32_t getFirmwareVersion();

    /// \brief Gets CPU temperature
    /// \param[in] channel - the channel to get data from
    double getTemperature(TemperatureChannelIndex channel);

    /// \brief Gets CPU fan speed
    /// \param[in] channel - the channel to get data from
    std::uint32_t getFanSpeed(FanChannelIndex channel);
    
    /// \brief Probe if GPIO direction can be set
    /// \param[in] channel - the channel to set, the direction to set
    bool canSetGpioDirection(GpioChannelIndex channel, GpioDirection direction) const;
    
    /// \brief Set GPIO direction
    /// \param[in] channel - the channel to set, the direction to set
    void setGpioDirection(GpioChannelIndex channel, GpioDirection direction);
    
    /// \brief Get GPIO direction
    /// \param[in] channel - the channel to get
    GpioInputValue getGpioInput(GpioChannelIndex channel);

protected:

	Device m_device;
};



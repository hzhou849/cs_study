//
// A "network data" event, generated when a network packet arrives.
//

#ifndef __EVENT_NETWORK_H__
#define __EVENT_NETWORK_H__

#include "Event.h"

namespace df {

const std::string NETWORK_EVENT = "df::network";

namespace Network {
enum Label {
  UNDEFINED_LABEL = -1,
  ACCEPT,
  CONNECT,
  CLOSE,
  DATA,
};  
} // namespace Network

class EventNetwork : public Event {

 private:
  EventNetwork();              // Must provide type in constructor.
  Network::Label m_label;      // Label, depending upon type.
  int m_socket_index;	       // Socket index of connection.
  int m_bytes;		       // Number of bytes avail (0 if connection).
  
 public:
  // Constructor must provide label.  
  EventNetwork(Network::Label label);

  // Set label.
  void setLabel(Network::Label new_label);

  // Get label.
  Network::Label getLabel() const;

  // Set socket index.
  void setSocketIndex(int new_socket_index);

  // Get socket_index.
  int getSocketIndex() const;

  // Set number of bytes available.
  void setBytes(int new_bytes);

  // Get number of bytes available.
  int getBytes() const;
};

} // end of namespace df

#endif // __EVENT_NETWORK_H__

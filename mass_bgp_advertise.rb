# ---------------------------------------------------
# mass_bgp_advertise.rb
# ---------------------------------------------------
# by PJO
#
# mass_bgp_advertise creates a bird configuration file with numerous static routes
# a bgp neighbor is creates to advertise those routes into a lab network
# in order to stress it

# Usage :
#  - install bird 2.0 on your linux system with
#       $ sudo apt install bird_bgp
#  - edit this file to change local and neighbor BGP informations
#  - optionnal : change the IP_BASE adress which is the first address
#    to be advertised
#  - create the bird.conf file with
#       $ ruby mass_bgp_advertise.rb <number of routes> >> bird.conf
#  - call bird to establish the peer and advertise fake routes
#       $ sudo /usr/local/sbin/bird -f -c bird.conf


IP_BASE = "11.0.0.1"          # first /32 to be advertised

LOCAL_AS  = "65000"           # bird AS number
REMOTE_AS = "65001"           # AS of remote peer
REMOTE_IP = "192.2.0.1"       # IP of remote peer

# do not change
# ------------------------------------------------------
require 'ipaddr'

# HEADER contains the fixed part of the bird configuration
# do not forget to change the local and neighbor informations
HEADER = "
# discover local interfaces to establish BGP peer
protocol device { scan time 15; };

# A fake router-id
router id 216.215.214.213;

# Declare BGP peer
protocol bgp PE {
#  debug { states, routes, interfaces, events, packets };
  debug { states, events };
  local    as #{LOCAL_AS};
  neighbor #{REMOTE_IP} as #{REMOTE_AS};
  ipv4 {
      import none;
      export where proto = \"fake4bgp\";
  } ;
};

# and begin config for tons of fake static routes
protocol static fake4bgp {
     ipv4;
"

TRAILER = "
};
"

# ------------------
# program begins Here (and it is very short)
# ------------------

# read Argument
N = ARGV[0].to_i

ip_next = ip_base = IPAddr.new IP_BASE

puts HEADER

N.times {
    puts "     route " + ip_next.to_s + "/32 blackhole;"
    ip_next = ip_next.succ
}

puts TRAILER


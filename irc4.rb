# ---------------------------------------------------------
# irc4.rb by Ph. Jounin 2018
#
# A poor implementation of an IRC Client
# wriiten to complete a root-me challenge
# ---------------------------------------------------------

require 'socket'
require "base64"
require "zlib"


CHALLENGE = "ep4"
USER = "ark"

def Dialog(ircskt, cmd, timer, debug)
  ircskt.puts(cmd)   if cmd!=nil
  puts "...waiting for #{debug} reply"
  sleep timer
  answer = ircskt.recv(10000)
  puts answer if debug
  return answer
end
   

# open connection to the chat bot and send authnetification
ircskt = TCPSocket.new("irc.root-me.org", 6667)
   Dialog ircskt, nil, 2, "connection"
   Dialog ircskt, "USER #{USER} * *: me\nNICK #{USER}", 3, "user"
   Dialog ircskt, "JOIN #root-me_challenge", 1, "join"
   answer= Dialog ircskt, "PRIVMSG candy !#{CHALLENGE}", 1, "privmsg"

   if match = answer.match( /#{USER} :(\S+)=/ )
       encoded = match.captures[0]
       puts "encoded msg is #{encoded}"
       rez = Zlib::Inflate.inflate (Base64.decode64(encoded) )
       answer = Dialog ircskt, "PRIVMSG candy !#{CHALLENGE} -rep #{rez}", 1, "reply"
       puts "-->#{answer}>"
   end


puts "Closing the Client..................."
ircskt.close                    # Close the socket

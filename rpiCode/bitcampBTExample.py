import bitcampBT
import urllib2
import urllib

unit_id = 1

#url = "/Zone"

#postStr = "id="
#postStr += str((unit_id))
#postStr += "signal_str="
#postStr += str(bitcampBT.getPower())
#postStr += "\r\n\r\n"

#data = "POST /Zone HTTP/1.1\r\n"
#data += "Host: 54.187.33.101\r\n"
#data += "Connection: close\r\n"
#data += "Content-Type: application/x-www-form-urlencoded\r\n"
#data += "Content-Length: "
#data += postStr

query_args = {'id' : unit_id,'signal_str' : bitcampBT.getPower()}

url = 'http://54.187.33.101:8080/Zone' 

data = urllib.urlencode(query_args)


request = urllib2.Request(url, data)

response = urllib2.urlopen(request).read()

print("Request sent!")

while True:
	if(bitcampBT.getPower()>0):
		query_args = {'id' : unit_id,'signal_str' : bitcampBT.getPower()}

		data = urllib.urlencode(query_args)


		request = urllib2.Request(url, data)

		print("Request sent!")

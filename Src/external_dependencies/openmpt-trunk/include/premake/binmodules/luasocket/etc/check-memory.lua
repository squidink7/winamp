	function load(s)
collectgarbage()
local a = gcinfo()
_G[s] = require(s)
collectgarbage()
local b = gcinfo()
print(s .. ":\t " .. (b-a) .. "k")
	end
	
	load("socket.url")
	load("ltn12")
	load("socket")
	load("mime")
	load("socket.tp")
	load("socket.smtp")
	load("socket.http")
	load("socket.ftp")
	
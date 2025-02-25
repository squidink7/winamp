				--
				-- tests/base/test_http.lua
				-- Tests the http API
				-- Copyright (c) 2016, 2020 Jason Perkins and the Premake project
				--
				
				if http.get ~= nil and _OPTIONS["test-all"] then
			local p = premake
				
			local suite = test.declare("premake_http")
				
				
			function suite.http_get()
		local result, err = http.get("http://httpbin.org/user-agent")
		if result then
	p.out(result)
	test.capture(
'{"user-agent": "Premake/' .. _PREMAKE_VERSION .. '"}'
	)
		else
	test.fail(err);
		end
			end
				
			function suite.https_get()
		-- sslverifypeer = 0, so we can test from within companies like here at Blizzard where all HTTPS traffic goes through
		-- some strange black box that re-signs all traffic with a custom ssl certificate.
		local result, err = http.get("https://httpbin.org/user-agent", { sslverifypeer = 0 })
		if result then
	p.out(result)
	test.capture(
'{"user-agent": "Premake/' .. _PREMAKE_VERSION .. '"}'
	)
		else
	test.fail(err);
		end
			end
				
			function suite.https_get_verify_peer()
		local result, err = http.get("https://httpbin.org/user-agent")
		if result then
	p.out(result)
	test.capture(
'{"user-agent": "Premake/' .. _PREMAKE_VERSION .. '"}'
	)
		else
	test.fail(err);
		end
			end
				
			function suite.http_responsecode()
		local result, err, responseCode = http.get("http://httpbin.org/status/418")
		test.isequal(responseCode, 418)
			end
				
			-- Disable as httpbin.org returns 404 on this endpoint
			-- See: https://github.com/postmanlabs/httpbin/issues/617
				
			--[[
			function suite.http_redirect()
		local result, err, responseCode = http.get("http://httpbin.org/redirect/3")
		if result then
	test.isequal(responseCode, 200)
		else
	test.fail(err);
		end
			end
			]]
				
			function suite.http_headers()
		local result, err, responseCode = http.get("http://httpbin.org/headers", {
	headers = { 'X-Premake: premake' }
		})
				
		if result then
	if (not result:find('X-Premake')) then
test.fail("response doens't contain header")
test.print(result)
	end
		else
	test.fail(err);
		end
			end
				
				end
				
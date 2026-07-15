local out = ""
local h = "0123456789ABCDEF"

for i = 1, 16 do
	for o = 1, 16 do
		out = out .. "\"" .. h:sub(i, i) .. h:sub(o, o) .. "\" \"\\0\" "
	end
end

print(out)

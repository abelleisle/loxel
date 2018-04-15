function fact(n)
	if n == 0 then
		return 1
	end
	return n * fact(n-1)
end

function hi()
	print("Hi")
end

-- stock
Stock = {name = "",
		 price = 0}

function Stock:new(o, name, price)
	o = o or {}
	setmetatable(o, self)
	self.__index = self
	self.name = name or ""
	self.price = price or 0
	return o
end

Coins = {Stock:new(nil, "Bitcoin", 19000),
		 Stock:new(nil, "Euthereum", 690),
		 Stock:new(nil, "Litecoin", 315)}

Table = {"meme",
		 {1,2,3},
		 "hey",
		 65}

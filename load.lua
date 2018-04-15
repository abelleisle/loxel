function place()
	print("Placed")
end

function updateGrass()
    print ("TODO update grass")
end

create_block({name = "Cobblestone",
			  id = 12,
		  	  durability = 43,
			  model = "img.svg",
			  onclick = place})

create_block({name = "Grass",
			  id = 16,
		  	  durability = 666,
			  model = "death.png",
			  onclick = updateGrass})

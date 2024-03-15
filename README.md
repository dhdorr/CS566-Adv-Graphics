# CS566-Adv-Graphics
CS566 Advanced Computer Graphics - Grad School

DEREK DORR


compile code with make,
run code with ./assignment_2 data/Model1

Problems:
 - mesh doesn't draw properly, although it looks like the file loads in correctly. I could not figure out this issue.
 - unclear how to draw mesh after vertices and faces have been loaded in.
 - stick figure joints can break when rotating. looks like some joints are controlling the parent skeleton's cube instead of just the children
    I think this is because of the way i traversed through the list of joints to draw the skeleton, like I'm off by one skeleton bone.
 - no SSD :(
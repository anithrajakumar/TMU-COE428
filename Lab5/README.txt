Everything in the lab worked correctly. There's another type of XML tag we didn't use called the stand-alone tag. These tags are special because 
they open and close themselves in one go. You can spot them by the / before the > at the end, like <foo/>.
To make the code handle these stand-alone tags, we'd need to make some changes. These tags don't need any stack 
operations since they're already balanced by themselves. They don't get pushed or popped like regular tags.
In the part1Main.c file, we'd add some extra checks to notice when we find one of these stand-alone tags. When we see 
that / before the >, we'll know it's a stand-alone tag. We might want to print a message saying we found one, just to keep track.
The rest of the validation would stay the same. Regular opening and closing tags would still work exactly like before. The 
stand-alone tags would just be a special case that gets handled separately. They wouldn't affect the stack at all.
This change would make the validator more complete since real XML files often use these self-closing tags. It wouldn't be 
too hard to add either, just some extra if-else statements to check for that / character before the tag ends.

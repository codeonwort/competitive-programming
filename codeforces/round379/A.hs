-- Codeforces Round #379 (Div. 2)
-- http://codeforces.com/contest/734

-- ID: 734A (Anton and Danik)

main = do
	n <- read `fmap` getLine :: IO Int
	s <- getLine
	let anton = length $ filter (== 'A') s
	let danik = length $ filter (== 'D') s
	if anton == danik
	then putStrLn "Friendship"
	else if anton > danik
	then putStrLn "Anton"
	else putStrLn "Danik"

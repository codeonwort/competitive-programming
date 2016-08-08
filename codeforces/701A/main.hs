import Data.List
import Control.Monad

getInt = read `fmap` getLine :: IO Int

pick2 ns n goal = f (zip [1..n] ns) n where
	f ns 0 = return []
	f ns n = do
		(i,x) <- ns
		let ns' = delete (i,x) ns
		(j,y) <- ns'
		let ns'' = delete (j,y) ns'
		guard $ (x+y) == goal
		rest <- f ns'' (n-2)
		return $ (i,x):(j,y):rest

same ((i,x):(j,y):ns) = f (x+y) ns where
	f z [] = True
	f z ((i,x):(j,y):ns)
		| z == x + y = f z ns
		| otherwise = False

main = do
	n <- getInt
	ns <- (map read . words) `fmap` getLine :: IO [Int]
	let goal = sum ns `div` (n `div` 2)
	let picks = pick2 ns n goal
	let soln = head (filter same picks)
	printSoln soln

printSoln [] = return ()
printSoln ((i,x):(j,y):ns) = do
	putStrLn $ show i ++ " " ++ show j
	printSoln ns

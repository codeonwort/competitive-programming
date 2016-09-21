import Control.Monad

main = do
	let n = 100000 
	let k = 10000000000
	-- n, k
	putStrLn $ show n ++ " " ++ show k
	-- links
	forM_ [1..n] $ \i -> do
		putStr $ if i == n then "0" else show i
		putChar ' '
	putStrLn ""
	-- weights
	replicateM_ n $ do
		putStr (show 1)
		putChar ' '

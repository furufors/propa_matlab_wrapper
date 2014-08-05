function [temperature]=temperature(lat,lon)
    % lat = Latitude (°)
    % lon = Logitude (°)
    % hs  = Earth station altitude (km)
    % E   = Link elevation angle (rad)
    % f   = Link frequency (GHz)
    % to  = Tilt polarization angle (°)
    % D   = Earth station antenna diameter (m)
    % eta = Earth station antenna efficiency
    % p   = Percentage of the time (%)
    
    [status, command_output] = system(['temperature.exe'...
                                ' ' num2str(lat) ...
                                ' ' num2str(lon)]);
        temperature = str2double(command_output);